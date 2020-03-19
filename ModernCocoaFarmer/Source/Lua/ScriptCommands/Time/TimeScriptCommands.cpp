#include "Lua/ScriptCommands/Time/TimeScriptCommands.h"
#include "Lua/ScriptCommands/Time/TimeNotifierScriptCommands.h"
#include "Lua/ScriptCommands/Time/TimeManagerScriptCommands.h"


namespace MCF::Lua::Time::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    TimeManagerScriptCommands::initialize();
    TimeNotifierScriptCommands::initialize();
  }
}