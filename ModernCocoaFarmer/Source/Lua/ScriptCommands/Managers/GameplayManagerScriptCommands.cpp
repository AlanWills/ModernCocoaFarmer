#include "Lua/ScriptCommands/Managers/GameplayManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Managers/GameplayManager.h"


namespace MCF
{
  namespace Lua
  {
    namespace GameplayManagerScriptCommands
    {
      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        CelesteEngine::Lua::registerHandleUserType<Managers::GameplayManager>(
          "GameplayManager",
          "startGameplay", &Managers::GameplayManager::startGameplay);
      }
    }
  }
}