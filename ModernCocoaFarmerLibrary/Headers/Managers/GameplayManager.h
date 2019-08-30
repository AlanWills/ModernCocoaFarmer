#pragma once

#include "Managers/InteractableBuildingsManager.h"
#include "Memory/Handle.h"


namespace CelesteEngine
{
  class Screen;
}

namespace MCF
{
  namespace Managers
  {
    class GameplayManager
    {
      public:
        GameplayManager();

        void startGameplay(const CelesteEngine::Handle<CelesteEngine::Screen>& screen);

      private:
        std::unique_ptr<InteractableBuildingsManager> m_interactableBuildingsManager;
    };
  }
}