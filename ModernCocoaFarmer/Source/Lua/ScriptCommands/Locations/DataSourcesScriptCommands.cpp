#include "Lua/ScriptCommands/Locations/DataSourcesScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "Locations/DataSources.h"

using namespace MCF::Locations;


namespace MCF::Lua::Locations::DataSourcesScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Celeste::Lua::LuaState::instance();
    sol::table dataSources = state.create_named_table("LocationsDataSources");
    dataSources["LOCATIONS"] = DataSources::LOCATIONS;
    dataSources["NAME"] = DataSources::NAME;
    dataSources["DESCRIPTION"] = DataSources::DESCRIPTION;
    dataSources["DAYS_TO_COMPLETE"] = DataSources::DAYS_TO_COMPLETE;
  }
}