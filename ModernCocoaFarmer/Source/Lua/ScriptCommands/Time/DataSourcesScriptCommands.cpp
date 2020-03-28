#include "Lua/ScriptCommands/Time/TimeManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "Time/DataSources.h"

using namespace MCF::Time;


namespace MCF::Lua::Time::DataSourcesScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Celeste::Lua::LuaState::instance();
    sol::table dataSources = state.create_named_table("TimeDataSources");
    dataSources["CURRENT_MONTH"] = DataSources::CURRENT_MONTH;
  }
}