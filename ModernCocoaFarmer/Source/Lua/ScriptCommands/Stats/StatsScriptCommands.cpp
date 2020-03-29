#include "Lua/ScriptCommands/Stats/StatsScriptCommands.h"
#include "Lua/ScriptCommands/Stats/DataSourcesScriptCommands.h"
#include "Lua/ScriptCommands/Stats/ModifierScriptCommands.h"


namespace MCF::Lua::Stats::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    DataSourcesScriptCommands::initialize();
    ModifierScriptCommands::initialize();
  }
}