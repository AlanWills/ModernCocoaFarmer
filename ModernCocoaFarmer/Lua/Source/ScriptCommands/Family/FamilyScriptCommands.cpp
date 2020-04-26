#include "ScriptCommands/Family/FamilyScriptCommands.h"
#include "ScriptCommands/Family/DataSourcesScriptCommands.h"
#include "ScriptCommands/Family/FamilyManagerScriptCommands.h"
#include "ScriptCommands/Family/ChildScriptCommands.h"


namespace MCF::Lua::Family::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    DataSourcesScriptCommands::initialize(state);
    FamilyManagerScriptCommands::initialize(state);
    ChildScriptCommands::initialize(state);
  }
}