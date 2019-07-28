#pragma once

#include <thread>
#include <atomic>


namespace CelesteEngine
{
  class ScreenManager;
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

        std::atomic<bool> m_isBroadcasting;
        std::thread m_communicationThread;
    };
  }
}