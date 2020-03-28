#include "Lua/ScriptCommands/Time/TimeScriptCommands.h"
#include "Lua/ScriptCommands/Time/TimeNotifierScriptCommands.h"
#include "Lua/ScriptCommands/Time/TimeManagerScriptCommands.h"
#include "Lua/ScriptCommands/Time/DataSourcesScriptCommands.h"


namespace MCF::Lua::Time::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    DataSourcesScriptCommands::initialize();
    TimeManagerScriptCommands::initialize();
    TimeNotifierScriptCommands::initialize();
  }
}