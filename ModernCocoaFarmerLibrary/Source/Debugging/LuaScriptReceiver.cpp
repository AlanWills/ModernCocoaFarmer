#include "Debugging/LuaScriptReceiver.h"
#include "Lua/LuaState.h"
#include "Debug/Debug.h"

namespace MCF
{
  namespace Debugging
  {
    //------------------------------------------------------------------------------------------------
    LuaScriptReceiver::LuaScriptReceiver() :
      m_isSending(false),
      m_listenThread(),
      m_sendThread(),
      m_incomingRequestQueueLock(),
      m_incomingRequestQueue(),
      m_outgoingResponseQueueLock(),
      m_outgoingResponseQueue(),
      m_server()
    {
    }

    //------------------------------------------------------------------------------------------------
    LuaScriptReceiver::~LuaScriptReceiver()
    {
      ASSERT(!m_isSending);
      ASSERT(!m_listenThread.joinable());
      ASSERT(!m_sendThread.joinable());
      ASSERT(!m_server.isConnected());
      ASSERT(!m_server.isConnecting());
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::start()
    {
      m_isSending = true;

      std::thread newListenThread(&LuaScriptReceiver::continuallyListenForRequests, this);
      m_listenThread.swap(newListenThread);

      std::thread newSendThread(&LuaScriptReceiver::continuallySendResponses, this);
      m_sendThread.swap(newSendThread);
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::continuallyListenForRequests()
    {
      m_server.setOnDataReceived([&](const char* data, int numReceivedBytes) -> void
      {
          std::lock_guard<std::mutex> lockGuard(m_incomingRequestQueueLock);
          std::string receiveBuffer;
          receiveBuffer.reserve(numReceivedBytes);

          for (int i = 0; i < numReceivedBytes; ++i)
          {
            receiveBuffer.push_back(data[i]);
          }

          m_incomingRequestQueue.push(receiveBuffer);
      });
      
      m_server.connectAsync(27015, [&]() -> void
      {
        m_server.receiveAsync();
      });
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::continuallySendResponses()
    {
      std::string response;

      while (m_isSending)
      {
        bool gotResponse = false;

        // Scope to minimise time spent using response queue lock
        {
          std::lock_guard<std::mutex> responseLockGuard(m_outgoingResponseQueueLock);

          if (!m_outgoingResponseQueue.empty())
          {
            response.assign(m_outgoingResponseQueue.front());
            m_outgoingResponseQueue.pop();
            gotResponse = true;
          }
        }

        if (gotResponse)
        {
          m_server.sendAsync(response);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::update()
    {
      bool gotRequest = false;
      std::string request;

      // Scope to minimise time spent using request queue lock
      {
        std::lock_guard<std::mutex> requestLockGuard(m_incomingRequestQueueLock);

        if (!m_incomingRequestQueue.empty())
        {
          request.assign(m_incomingRequestQueue.front());
          m_incomingRequestQueue.pop();
          gotRequest = true;
        }
      }

      if (gotRequest)
      {
        auto functionResult = CelesteEngine::Lua::LuaState::script(request);
        std::lock_guard<std::mutex> responseLockGuard(m_outgoingResponseQueueLock);

        if (!functionResult.valid())
        {
          sol::error error = functionResult;
          m_outgoingResponseQueue.push(error.what());
        }
        else if (functionResult.return_count() == 1)
        {
          m_outgoingResponseQueue.push(functionResult.get<std::string>(0));
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::stop()
    {
      m_isSending = false;

      m_server.disconnect();

      if (m_listenThread.joinable())
      {
        m_listenThread.join();
      }

      if (m_sendThread.joinable())
      {
        m_sendThread.join();
      }
    }
  }
}