#include "ScriptCommands/Family/FamilyManagerScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Family/DataSources.h"

using namespace MCF::Family;


namespace MCF::Lua::Family::DataSourcesScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    sol::table dataSources = state.create_named_table("FamilyDataSources");
    dataSources["HAS_SELECTED_CHILD"] = DataSources::HAS_SELECTED_CHILD;
    dataSources["SELECTED_CHILD_NAME"] = DataSources::SELECTED_CHILD_NAME;
    dataSources["CHILDREN"] = DataSources::CHILDREN;
    dataSources["IS_SELECTED"] = DataSources::IS_SELECTED;
    dataSources["IS_AT_LOCATION"] = DataSources::IS_AT_LOCATION;
    dataSources["CURRENT_LOCATION"] = DataSources::CURRENT_LOCATION;
  }
}