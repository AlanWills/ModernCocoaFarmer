#include "ScriptCommands/GameEvents/GameEventsScriptCommands.h"
#include "ScriptCommands/GameEvents/GameEventManagerScriptCommands.h"
#include "ScriptCommands/GameEvents/GameEventScriptCommands.h"

#include "ScriptCommands/GameEvents/Conditions/ConditionsScriptCommands.h"
#include "ScriptCommands/GameEvents/Effects/EffectsScriptCommands.h"


namespace MCF::Lua::GameEvents::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Conditions::ScriptCommands::initialize(state);
    Effects::ScriptCommands::initialize(state);

    GameEventManagerScriptCommands::initialize(state);
    GameEventScriptCommands::initialize(state);
  }
}