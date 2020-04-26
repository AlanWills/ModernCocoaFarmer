#include "ScriptCommands/Stats/StatsScriptCommands.h"
#include "ScriptCommands/Stats/DataSourcesScriptCommands.h"
#include "ScriptCommands/Stats/ModifierScriptCommands.h"


namespace MCF::Lua::Stats::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    DataSourcesScriptCommands::initialize(state);
    ModifierScriptCommands::initialize(state);
  }
}