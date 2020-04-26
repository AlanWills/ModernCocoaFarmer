#include "ScriptCommands/Locations/LocationsScriptCommands.h"
#include "ScriptCommands/Locations/DataSourcesScriptCommands.h"
#include "ScriptCommands/Locations/LocationScriptCommands.h"
#include "ScriptCommands/Locations/LocationManagerScriptCommands.h"


namespace MCF::Lua::Locations::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    DataSourcesScriptCommands::initialize(state);
    LocationScriptCommands::initialize(state);
    LocationManagerScriptCommands::initialize(state);
  }
}