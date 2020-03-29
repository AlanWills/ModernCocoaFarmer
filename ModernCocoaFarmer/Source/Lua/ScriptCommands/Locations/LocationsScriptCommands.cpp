#include "Lua/ScriptCommands/Locations/LocationsScriptCommands.h"
#include "Lua/ScriptCommands/Locations/DataSourcesScriptCommands.h"
#include "Lua/ScriptCommands/Locations/LocationScriptCommands.h"
#include "Lua/ScriptCommands/Locations/LocationManagerScriptCommands.h"


namespace MCF::Lua::Locations::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    DataSourcesScriptCommands::initialize();
    LocationScriptCommands::initialize();
    LocationManagerScriptCommands::initialize();
  }
}