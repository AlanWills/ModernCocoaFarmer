#include "ScriptCommands/Time/TimeScriptCommands.h"
#include "ScriptCommands/Time/TimeNotifierScriptCommands.h"
#include "ScriptCommands/Time/TimeManagerScriptCommands.h"
#include "ScriptCommands/Time/DataSourcesScriptCommands.h"


namespace MCF::Lua::Time::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    DataSourcesScriptCommands::initialize(state);
    TimeManagerScriptCommands::initialize(state);
    TimeNotifierScriptCommands::initialize(state);
  }
}