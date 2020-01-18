#include "Lua/ScriptCommands/Buildings/BuildingsScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingManagerScriptCommands.h"


namespace MCF::Lua::Buildings::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    BuildingScriptCommands::initialize();
    BuildingManagerScriptCommands::initialize();
  }
}