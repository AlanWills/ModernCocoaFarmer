#include "Locations/LocationsManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Locations/Location.h"
#include "Time/TimeManager.h"
#include "Money/MoneyManager.h"


namespace MCF::Locations
{
  REGISTER_UNMANAGED_COMPONENTABLE_OBJECT(LocationsManager);

  //------------------------------------------------------------------------------------------------
  const char* const LocationsManager::LOCATIONS_ELEMENT_NAME = "Locations";
  const char* const LocationsManager::LOCATION_ELEMENT_NAME = "Location";

  //------------------------------------------------------------------------------------------------
  LocationsManager::LocationsManager() :
    m_locations()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool LocationsManager::doDeserialize(const tinyxml2::XMLElement* element)
  {
    if (!Celeste::XML::hasChildElement(element, LOCATIONS_ELEMENT_NAME))
    {
      return true;
    }

    std::vector<std::string> locationPrefabs;
    Celeste::XML::XMLValueError result = Celeste::XML::getChildElementDataAsVector(element, LOCATIONS_ELEMENT_NAME, LOCATION_ELEMENT_NAME, locationPrefabs);
    
    if (result == Celeste::XML::XMLValueError::kError)
    {
      ASSERT_FAIL();
      return false;
    }

    for (const std::string& locationPrefab : locationPrefabs)
    {
      std::unique_ptr<Location> location = ScriptableObject::load<Location>(locationPrefab);
      ASSERT(location != nullptr);

      if (location != nullptr)
      {
        m_locations.emplace(location->getName(), std::move(location));
      }
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Location> LocationsManager::getLocation(const std::string& locationName)
  {
    auto locationIt = m_locations.find(locationName);
    return locationIt != m_locations.end() ? locationIt->second.get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::sendChildToLocation(Location& location, Family::Child& child)
  {
    location.sendChild(child);
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::onDayPassed()
  {
    for (const auto& locationPair : m_locations)
    {
      locationPair.second->onDayPassed();
    }
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::checkLocationsForChildrenLeaving(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager,
    Notifications::NotificationManager& notificationManager)
  {
    for (const auto& locationPair : m_locations)
    {
      locationPair.second->checkForChildrenLeaving(moneyManager, familyManager, *this, notificationManager);
    }
  }
}