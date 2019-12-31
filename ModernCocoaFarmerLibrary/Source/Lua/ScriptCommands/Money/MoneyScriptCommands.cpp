#include "Lua/ScriptCommands/Money/MoneyScriptCommands.h"
#include "Lua/ScriptCommands/Money/MoneyManagerScriptCommands.h"


namespace MCF::Lua::Money::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    MoneyManagerScriptCommands::initialize();
  }
}