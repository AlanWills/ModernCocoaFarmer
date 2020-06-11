#include "ScriptCommands/Money/MoneyScriptCommands.h"
#include "ScriptCommands/Money/MoneyManagerScriptCommands.h"


namespace MCF::Lua::Money::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    MoneyManagerScriptCommands::initialize(state);
  }
}