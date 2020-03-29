#include "Lua/ScriptCommands/GameEvents/GameEventScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "GameEvents/GameEvent.h"


namespace sol
{
  template <>
  struct is_to_stringable<MCF::GameEvents::GameEvent> : std::false_type {};
}

namespace MCF::Lua::GameEvents::GameEventScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using GameEvent = MCF::GameEvents::GameEvent;

    Celeste::Lua::registerScriptableObjectUserType<GameEvent>(
      GameEvent::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>());
  }
}