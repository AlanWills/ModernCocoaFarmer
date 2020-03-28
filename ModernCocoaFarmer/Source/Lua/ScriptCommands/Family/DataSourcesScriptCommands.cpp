#include "Lua/ScriptCommands/Family/FamilyManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "Family/DataSources.h"

using namespace MCF::Family;


namespace MCF::Lua::Family::DataSourcesScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Celeste::Lua::LuaState::instance();
    sol::table dataSources = state.create_named_table("FamilyDataSources");
    dataSources["CHILD_SELECTION_STATUS"] = DataSources::CHILD_SELECTION_STATUS;
  }
}