#include "ScriptCommands/GameEvents/Conditions/ConditionsScriptCommands.h"
#include "ScriptCommands/GameEvents/Conditions/LuaConditionScriptCommands.h"


namespace MCF::Lua::GameEvents::Conditions::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    LuaConditionScriptCommands::initialize(state);
  }
}