#include "Lua/ScriptCommands/Locations/LocationManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Locations/LocationsManager.h"
#include "Locations/Location.h"
#include "Family/Child.h"

using namespace MCF::Locations;


namespace MCF::Lua::Locations::LocationManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void activateLocation(LocationsManager& locationsManager, const std::string& locationName)
    {
      observer_ptr<Location> location = locationsManager.getLocation(locationName);
      ASSERT(location)

      if (location != nullptr)
      {
        locationsManager.activateLocation(*location);
      }
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnLocationActivatedCallback(
      LocationsManager& locationsManager, 
      sol::function callback, 
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<LocationsManager::LocationActivatedEvent, Location&>(
        locationsManager.getOnLocationActivatedEvent(),
        callback,
        extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using LocationsManager = MCF::Locations::LocationsManager;

    Celeste::Lua::registerScriptableObjectUserType<LocationsManager>(
      LocationsManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "getNumLocations", &LocationsManager::getNumLocations,
      "getLocation", &LocationsManager::getLocation,
      "activateLocation", &Internals::activateLocation,
      "subscribeOnLocationActivatedCallback", &Internals::subscribeOnLocationActivatedCallback);
  }
}