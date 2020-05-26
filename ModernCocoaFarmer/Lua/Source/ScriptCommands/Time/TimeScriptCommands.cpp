#include "ScriptCommands/Time/TimeScriptCommands.h"
#include "ScriptCommands/Time/TimeNotifierScriptCommands.h"
#include "ScriptCommands/Time/TimeManagerScriptCommands.h"


namespace MCF::Lua::Time::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    TimeManagerScriptCommands::initialize(state);
    TimeNotifierScriptCommands::initialize(state);
  }
}