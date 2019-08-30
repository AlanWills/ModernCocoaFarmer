#include "Managers/GameplayManager.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Screens/Screen.h"


namespace MCF
{
  namespace Managers
  {
    //------------------------------------------------------------------------------------------------
    GameplayManager::GameplayManager() :
      m_interactableBuildingsManager(nullptr)
    {
    }

    //------------------------------------------------------------------------------------------------
    void GameplayManager::startGameplay(const CelesteEngine::Handle<CelesteEngine::Screen>& screen)
    {
      m_interactableBuildingsManager.reset(new InteractableBuildingsManager());
      m_interactableBuildingsManager->initialize(screen);
    }
  }
}