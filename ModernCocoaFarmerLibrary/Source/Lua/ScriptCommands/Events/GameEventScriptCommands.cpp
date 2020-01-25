#include "Lua/ScriptCommands/Events/GameEventScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Events/GameEvent.h"


namespace MCF::Lua::Events::GameEventScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using GameEvent = MCF::Events::GameEvent;

    CelesteEngine::Lua::registerScriptableObjectUserType<GameEvent>(
      GameEvent::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>());
  }
}