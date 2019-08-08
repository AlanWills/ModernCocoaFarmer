#include "Debugging/LuaScriptReceiver.h"


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
      m_isListening = false;
      m_isSending = false;
      m_listenThread.join();
      m_sendThread.join();
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
      m_server.Connect(27015);

      // Receive request
      // Add request to request queue (checking mutex)
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::continuallySendResponses()
    {
      // Pop response off response queue
      // Send response
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::processRequest()
    {
      // Pop first request off request queue (checking mutex)
      // Run it
      // Get response and add onto outgoing response queue
    }
  }
}