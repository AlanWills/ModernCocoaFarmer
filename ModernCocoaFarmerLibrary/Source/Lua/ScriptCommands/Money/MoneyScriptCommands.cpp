#include "Lua/ScriptCommands/Money/MoneyScriptCommands.h"
#include "Lua/ScriptCommands/Money/DataSourcesScriptCommands.h"
#include "Lua/ScriptCommands/Money/MoneyManagerScriptCommands.h"


namespace MCF::Lua::Money::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    DataSourcesScriptCommands::initialize();
    MoneyManagerScriptCommands::initialize();
  }
}