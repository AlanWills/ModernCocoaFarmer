#include "ScriptCommands/Money/MoneyScriptCommands.h"
#include "ScriptCommands/Money/DataSourcesScriptCommands.h"
#include "ScriptCommands/Money/MoneyManagerScriptCommands.h"


namespace MCF::Lua::Money::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    DataSourcesScriptCommands::initialize(state);
    MoneyManagerScriptCommands::initialize(state);
  }
}