#include "ScriptCommands/Stats/DataSourcesScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Stats/DataSources.h"

using namespace MCF::Stats;


namespace MCF::Lua::Stats::DataSourcesScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    sol::table dataSources = state.create_named_table("StatsDataSources");
    dataSources["HEALTH"] = DataSources::HEALTH;
    dataSources["SAFETY"] = DataSources::SAFETY;
    dataSources["EDUCATION"] = DataSources::EDUCATION;
    dataSources["HAPPINESS"] = DataSources::HAPPINESS;
    dataSources["MONEY"] = DataSources::MONEY;
    dataSources["IS_DELTA"] = DataSources::IS_DELTA;
    dataSources["AMOUNT"] = DataSources::AMOUNT;
  }
}