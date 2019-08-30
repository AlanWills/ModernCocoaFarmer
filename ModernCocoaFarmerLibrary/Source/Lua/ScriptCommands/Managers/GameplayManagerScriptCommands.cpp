#include "Lua/ScriptCommands/Managers/GameplayManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Managers/GameplayManager.h"
#include "Game/MCFGame.h"


namespace MCF
{
  namespace Lua
  {
    namespace GameplayManagerScriptCommands
    {
      namespace Internals
      {
        Managers::GameplayManager* getGameplayManager()
        {
          return static_cast<MCFGame*>(CelesteEngine::Game::current())->getGameplayManager().get();
        }
      }

      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        CelesteEngine::Lua::registerUserType<Managers::GameplayManager>(
          "GameplayManager",
          "instance", &Internals::getGameplayManager,
          "startGameplay", &Managers::GameplayManager::startGameplay);
      }
    }
  }
}