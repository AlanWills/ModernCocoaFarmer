#include "Lua/ScriptCommands/Events/GameEventManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Events/GameEventManager.h"

using namespace MCF::Events;


namespace MCF::Lua::Events::GameEventManagerScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CelesteEngine::Lua::registerScriptableObjectUserType<GameEventManager>(
      GameEventManager::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>());
  }
}