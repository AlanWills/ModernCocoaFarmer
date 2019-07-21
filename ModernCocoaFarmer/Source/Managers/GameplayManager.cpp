#include "Managers/GameplayManager.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF
{
  namespace Managers
  {
    REGISTER_SCRIPT(GameplayManager, 1)

    //------------------------------------------------------------------------------------------------
    GameplayManager::GameplayManager() :
      m_interactableBuildingsManager(nullptr)
    {
    }

    //------------------------------------------------------------------------------------------------
    GameplayManager::~GameplayManager()
    {
    }

    //------------------------------------------------------------------------------------------------
    void GameplayManager::onInitialize()
    {
      ASSERT(m_interactableBuildingsManager.get() == nullptr);
      m_interactableBuildingsManager.reset(new InteractableBuildingsManager());
    }

    //------------------------------------------------------------------------------------------------
    void GameplayManager::onDeath()
    {
      ASSERT(m_interactableBuildingsManager.get() != nullptr);
      m_interactableBuildingsManager.reset(nullptr);
    }

    //------------------------------------------------------------------------------------------------
    void GameplayManager::startGameplay()
    {
      m_interactableBuildingsManager->initialize(getGameObject()->getScreen());
    }
  }
}