#include "ScriptCommands/Locations/LocationManagerScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Locations/LocationsManager.h"
#include "Locations/Location.h"
#include "Family/Child.h"

using namespace MCF::Locations;


namespace sol
{
  template <>
  struct is_to_stringable<LocationsManager> : std::false_type {};
}

namespace MCF::Lua::Locations::LocationManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void activateLocation(LocationsManager& locationsManager, const std::string& locationName)
    {
      observer_ptr<Location> location = locationsManager.findLocation(locationName);
      ASSERT(location);

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
  void initialize(sol::state& state)
  {
    using LocationsManager = MCF::Locations::LocationsManager;

    Celeste::Lua::registerScriptableObjectUserType<LocationsManager>(
      state,
      LocationsManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "setDataStore", &LocationsManager::setDataStore,
      "getNumLocations", &LocationsManager::getNumLocations,
      "findLocation", &LocationsManager::findLocation,
      "activateLocation", &Internals::activateLocation,
      "subscribeOnLocationActivatedCallback", &Internals::subscribeOnLocationActivatedCallback);
  }
}