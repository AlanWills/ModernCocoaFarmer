#include "ScriptCommands/Data/DataSystemScriptCommands.h"


namespace MCF::Lua::Data::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Data::DataSystemScriptCommands::initialize(state);
  }
}