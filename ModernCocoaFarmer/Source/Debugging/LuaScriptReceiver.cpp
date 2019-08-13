#include "Debugging/LuaScriptReceiver.h"
#include "Lua/LuaState.h"
#include "Debug/Debug.h"

namespace MCF
{
  namespace Debugging
  {
    //------------------------------------------------------------------------------------------------
    LuaScriptReceiver::LuaScriptReceiver() :
      m_isListening(false),
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
      //m_isListening = false;
      //m_isSending = false;
      bool listenThreadJoined = false;
      bool sendThreadJoined = false;

      if (m_listenThread.joinable())
      {
        m_listenThread.join();
        listenThreadJoined = true;
      }

      if (m_sendThread.joinable())
      {
        m_sendThread.join();
        sendThreadJoined = true;
      }
      
      m_server.disconnect();

      while (!m_incomingRequestQueueLock.try_lock())
      {
        ASSERT(listenThreadJoined);
        std::string error;
      }
      m_incomingRequestQueueLock.unlock();

      while (!m_outgoingResponseQueueLock.try_lock())
      {
        ASSERT(sendThreadJoined);
        std::string error;
      }
      m_outgoingResponseQueueLock.unlock();
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::start()
    {
      m_isListening = true;
      m_isSending = true;
      m_listenThread.swap(std::thread(&LuaScriptReceiver::continuallyListenForRequests, this));
      m_sendThread.swap(std::thread(&LuaScriptReceiver::continuallySendResponses, this));
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::continuallyListenForRequests()
    {
      m_server.connect(27015);
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

      m_server.receiveAsync();
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

      ASSERT_FAIL();
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
  }
}