#include "ScriptCommands/Data/DataSystemScriptCommands.h"
#include "ScriptCommands/Data/ObjectRefScriptCommands.h"
#include "ScriptCommands/Data/Constants/ConstantScriptCommands.h"


namespace MCF::Lua::Data::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Data::DataSystemScriptCommands::initialize(state);
    Data::ObjectRefScriptCommands::initialize(state);
    Data::ConstantScriptCommands::initialize(state);
  }
}