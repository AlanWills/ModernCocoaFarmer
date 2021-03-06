#include "ScriptCommands/Locations/DataSourcesScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Locations/DataSources.h"

using namespace MCF::Locations;


namespace MCF::Lua::Locations::DataSourcesScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    sol::table dataSources = state.create_named_table("LocationsDataSources");
    dataSources["LOCATIONS"] = DataSources::LOCATIONS;
    dataSources["DAYS_TO_COMPLETE"] = DataSources::DAYS_TO_COMPLETE;
  }
}