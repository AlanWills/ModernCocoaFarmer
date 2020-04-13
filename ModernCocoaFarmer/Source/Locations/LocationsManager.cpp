#include "Locations/LocationsManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Locations/Location.h"
#include "Locations/DataSources.h"
#include "Stats/DataSources.h"
#include "Stats/Modifier.h"
#include "Persistence/DataObjectHandle.h"
#include "Time/TimeManager.h"
#include "Money/MoneyManager.h"


namespace MCF::Locations
{
  REGISTER_SCRIPTABLE_OBJECT(LocationsManager);

  //------------------------------------------------------------------------------------------------
  const char* const LocationsManager::LOCATIONS_ELEMENT_NAME = "Locations";
  const char* const LocationsManager::LOCATION_ELEMENT_NAME = "Location";

  //------------------------------------------------------------------------------------------------
  LocationsManager::LocationsManager() :
    m_locations(),
    m_onLocationActivatedEvent()
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
  observer_ptr<Location> LocationsManager::findLocation(const std::string& locationName) const
  {
    auto locationIt = m_locations.find(locationName);
    return locationIt != m_locations.end() ? locationIt->second.get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::activateLocation(Location& location)
  {
    m_onLocationActivatedEvent.invoke(location);
    updateDataStore();
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
  void LocationsManager::checkLocationsForChildrenArriving(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager,
    Notifications::NotificationManager& notificationManager)
  {
    for (const auto& locationPair : m_locations)
    {
      locationPair.second->checkForChildrenArriving(moneyManager, familyManager, *this, notificationManager);
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

  //------------------------------------------------------------------------------------------------
  void LocationsManager::setDataStore(observer_ptr<Persistence::DataStore> dataStore)
  {
    m_dataStore = dataStore;
    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::updateDataStore()
  {
    if (m_dataStore != nullptr && !m_suspendDataStoreUpdates)
    {
      for (const auto& locationPair : m_locations)
      {
        Location& location = *locationPair.second;

        std::string locationKey(DataSources::LOCATIONS);
        locationKey.push_back('.');
        locationKey.append(location.getName());

        Persistence::DataObjectHandle locationObject(*m_dataStore, locationKey);
        locationObject.set(DataSources::NAME, location.getName());
        locationObject.set(DataSources::DESCRIPTION, location.getDescription());
        locationObject.set(DataSources::DAYS_TO_COMPLETE, location.getDaysToComplete());

        writeModifier(locationKey, Stats::DataSources::EDUCATION, location.getEducationModifier());
        writeModifier(locationKey, Stats::DataSources::HAPPINESS, location.getHappinessModifier());
        writeModifier(locationKey, Stats::DataSources::HEALTH, location.getHealthModifier());
        writeModifier(locationKey, Stats::DataSources::MONEY, location.getMoneyModifier());
        writeModifier(locationKey, Stats::DataSources::SAFETY, location.getSafetyModifier());
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::writeModifier(
    const std::string& locationKey, 
    const char* const modifierKey, 
    const Stats::Modifier& modifier)
  {
    std::string key(locationKey);
    key.push_back('.');
    key.append(modifierKey);

    Persistence::DataObjectHandle locationObject(*m_dataStore, key);
    locationObject.set(Stats::DataSources::IS_DELTA, modifier.getChangeType() == Stats::ChangeType::kDelta);
    locationObject.set(Stats::DataSources::AMOUNT, modifier.getAmount());
  }
}