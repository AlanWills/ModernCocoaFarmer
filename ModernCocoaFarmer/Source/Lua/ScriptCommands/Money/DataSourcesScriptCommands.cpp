#include "Lua/ScriptCommands/Money/MoneyManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "Money/DataSources.h"

using namespace MCF::Money;


namespace MCF::Lua::Money::DataSourcesScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Celeste::Lua::LuaState::instance();
    sol::table dataSources = state.create_named_table("MoneyDataSources");
    dataSources["CURRENT_MONEY"] = DataSources::CURRENT_MONEY;
    dataSources["CURRENT_SALARY_LEVEL"] = DataSources::CURRENT_SALARY_LEVEL;
  }
}