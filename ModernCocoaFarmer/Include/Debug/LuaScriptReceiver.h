#pragma once

#include "Networking/SocketServer.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <queue>


namespace MCF
{
  namespace Debugging
  {
    class LuaScriptReceiver
    {
      public:
        LuaScriptReceiver();
        LuaScriptReceiver(const LuaScriptReceiver&) = delete;
        LuaScriptReceiver(LuaScriptReceiver&&) = default;
        ~LuaScriptReceiver();

        LuaScriptReceiver& operator=(const LuaScriptReceiver&) = delete;

        void start();
        void update();
        void stop();

      private:
        void continuallyListenForRequests();
        void continuallySendResponses();

        std::atomic<bool> m_isSending;

        std::thread m_listenThread;
        std::thread m_sendThread;

        std::mutex m_incomingRequestQueueLock;
        std::queue<std::string> m_incomingRequestQueue;

        std::mutex m_outgoingResponseQueueLock;
        std::queue<std::string> m_outgoingResponseQueue;

        Networking::SocketServer m_server;
    };
  }
}