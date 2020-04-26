#include "ScriptCommands/GameEvents/Effects/EffectsScriptCommands.h"
#include "ScriptCommands/GameEvents/Effects/LuaEffectScriptCommands.h"


namespace MCF::Lua::GameEvents::Effects::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    LuaEffectScriptCommands::initialize(state);
  }
}