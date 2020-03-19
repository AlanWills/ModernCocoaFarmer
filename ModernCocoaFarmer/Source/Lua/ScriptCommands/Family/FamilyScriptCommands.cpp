#include "Lua/ScriptCommands/Family/FamilyScriptCommands.h"
#include "Lua/ScriptCommands/Family/FamilyManagerScriptCommands.h"
#include "Lua/ScriptCommands/Family/ChildScriptCommands.h"


namespace MCF::Lua::Family::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    FamilyManagerScriptCommands::initialize();
    ChildScriptCommands::initialize();
  }
}