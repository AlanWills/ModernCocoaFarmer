#pragma once

#include "Networking/SocketServer.h"

#include <thread>
#include <atomic>
#include <string>


namespace CelesteEngine
{
  class ScreenManager;
  class GameObject;
}

namespace MCF
{
  namespace Debugging
  {
    class SceneBroadcaster
    {
      public:
        SceneBroadcaster();
        SceneBroadcaster(const SceneBroadcaster&) = delete;
        SceneBroadcaster(SceneBroadcaster&&) = default;
        ~SceneBroadcaster();

        SceneBroadcaster& operator=(const SceneBroadcaster&) = delete;

        void startBroadcasting(const CelesteEngine::ScreenManager& screenManager);

      private:
        void continuallySendData(const CelesteEngine::ScreenManager& screenManager);
        void serializeGameObject(CelesteEngine::GameObject& gameObject, std::string& output) const;

        std::atomic<bool> m_isBroadcasting;
        std::thread m_communicationThread;

        Networking::SocketServer m_server;

        static const char m_fieldDelimiter;
        static const char m_vectorDelimiter;
        static const char* m_messageEndDelimiter;
    };
  }
}