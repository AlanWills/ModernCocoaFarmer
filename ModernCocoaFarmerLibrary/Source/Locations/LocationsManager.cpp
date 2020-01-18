#include "Locations/LocationsManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Locations/Location.h"
#include "Time/TimeManager.h"
#include "Money/MoneyManager.h"
#include "Events/EventArgs.h"


namespace MCF::Locations
{
  REGISTER_SCRIPTABLE_OBJECT(LocationsManager);

  //------------------------------------------------------------------------------------------------
  const char* const LocationsManager::LOCATIONS_ELEMENT_NAME = "Locations";
  const char* const LocationsManager::LOCATION_ELEMENT_NAME = "Location";

  //------------------------------------------------------------------------------------------------
  LocationsManager::LocationsManager() :
    m_timeManager(nullptr),
    m_locations(),
    m_onDayPassedHandle(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  bool LocationsManager::doDeserialize(const tinyxml2::XMLElement* element)
  {
    if (!hasChildElement(element, LOCATIONS_ELEMENT_NAME))
    {
      return true;
    }

    std::vector<std::string> locationPrefabs;
    XMLValueError result = getChildElementDataAsVector(element, LOCATIONS_ELEMENT_NAME, LOCATION_ELEMENT_NAME, locationPrefabs);
    
    if (result == XMLValueError::kError)
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
  void LocationsManager::setTimeManager(observer_ptr<Time::TimeManager> timeManager)
  {
    if (m_timeManager != nullptr)
    {
      m_timeManager->getOnDayPassedEvent().unsubscribe(m_onDayPassedHandle);
    }

    m_timeManager = timeManager;

    if (m_timeManager != nullptr)
    {
      m_onDayPassedHandle = m_timeManager->getOnDayPassedEvent().subscribe([this](CelesteEngine::EventArgs&) { onDayPassed(); });
    }
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::sendChildToLocation(Location& location, Family::Child& child)
  {
    location.sendChild(child);
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::onDayPassed()
  {
    for (const auto& stringLocationPair : m_locations)
    {
      stringLocationPair.second->updateCurrentChildren();
    }
  }
}