#include "ScriptCommands/GameEvents/Conditions/LuaConditionScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "GameEvents/Conditions/LuaCondition.h"


namespace MCF::Lua::GameEvents::Conditions::LuaConditionScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using namespace MCF::GameEvents::Conditions;

    Celeste::Lua::registerScriptableObjectUserType<LuaCondition>(
      state,
      LuaCondition::type_name(),
      sol::base_classes, sol::bases<Condition, Celeste::ScriptableObject>(),
      "setIsConditionMetFunc", &LuaCondition::setIsConditionMetFunc);
  }
}