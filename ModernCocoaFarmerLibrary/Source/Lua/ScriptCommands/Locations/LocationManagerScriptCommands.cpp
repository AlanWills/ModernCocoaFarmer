#include "Lua/ScriptCommands/Locations/LocationManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Locations/LocationsManager.h"
#include "Locations/Location.h"
#include "Family/Child.h"


namespace MCF::Lua::Locations::LocationManagerScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using LocationsManager = MCF::Locations::LocationsManager;

    CelesteEngine::Lua::registerScriptableObjectUserType<LocationsManager>(
      LocationsManager::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "getNumLocations", &LocationsManager::getNumLocations,
      "getLocation", &LocationsManager::getLocation,
      "setTimeManager", &LocationsManager::setTimeManager);
  }
}