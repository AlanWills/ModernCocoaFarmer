#pragma once

#include "Objects/Script.h"
#include "Managers/InteractableBuildingsManager.h"


namespace MCF
{
  namespace Managers
  {
    class GameplayManager : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(GameplayManager)

      public:
        void startGameplay();

      protected:
        void onInitialize() override;
        void onDeath() override;

      private:
        std::unique_ptr<InteractableBuildingsManager> m_interactableBuildingsManager;
    };
  }
}