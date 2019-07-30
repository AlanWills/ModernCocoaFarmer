#pragma once

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
        void continuallySendData(const CelesteEngine::ScreenManager& screenManager) const;
        void serializeGameObject(CelesteEngine::GameObject& gameObject, std::string& output) const;

        std::atomic<bool> m_isBroadcasting;
        std::thread m_communicationThread;

        static char m_delimiter;
    };
  }
}