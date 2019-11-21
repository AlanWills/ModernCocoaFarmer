#include "Lua/ScriptCommands/Family/FamilyScriptCommands.h"
#include "Lua/ScriptCommands/Family/ChildInformationScriptCommands.h"


namespace MCF::Lua::Family::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    ChildInformationScriptCommands::initialize();
  }
}