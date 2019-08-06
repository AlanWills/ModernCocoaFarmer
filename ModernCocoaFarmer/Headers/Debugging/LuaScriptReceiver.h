#pragma once

#include <thread>
#include <atomic>

#include "Networking/SocketServer.h"


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

        void startListening() const;

      private:
        std::atomic<bool> m_isListening;
        std::thread m_communicationThread;

        Networking::SocketServer m_server;
    };
  }
}