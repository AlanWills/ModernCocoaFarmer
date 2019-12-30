#include "Lua/ScriptCommands/Buildings/BuildingsScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingInformationScriptCommands.h"


namespace MCF::Lua::Buildings::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    BuildingInformationScriptCommands::initialize();
  }
}