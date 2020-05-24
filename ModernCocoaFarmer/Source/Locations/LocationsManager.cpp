#include "Locations/LocationsManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Locations/Location.h"
#include "Locations/DataSources.h"
#include "Stats/DataSources.h"
#include "Stats/Modifier.h"
#include "Data/DataSystem.h"

using namespace Celeste::XML;


namespace MCF::Locations
{
  REGISTER_SCRIPTABLE_OBJECT(LocationsManager);

  //------------------------------------------------------------------------------------------------
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
    for (const tinyxml2::XMLElement* locationElement : children(element, Location::type_name()))
    {
      m_locations.push_back(deserializeScriptableObject<Location>(locationElement));
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Location> LocationsManager::getLocation(size_t index)
  {
    return index < m_locations.size() ? &m_locations[index].get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Location> LocationsManager::findLocation(const std::string& locationName) const
  {
    auto locationIt = std::find_if(m_locations.begin(), m_locations.end(),
      [&locationName](const std::reference_wrapper<Location>& location)
      {
        return location.get().getName() == locationName;
      });
    return locationIt != m_locations.end() ? &locationIt->get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::activateLocation(Location& location)
  {
    m_onLocationActivatedEvent.invoke(location);
    updateDataSystem();
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::setDataSystem(observer_ptr<Data::DataSystem> dataSystem)
  {
    m_dataSystem = dataSystem;
    updateDataSystem();
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::updateDataSystem()
  {
    if (m_dataSystem != nullptr)
    {
      for (const auto& locationRef : m_locations)
      {
        Location& location = locationRef.get();
        
        std::string locationKey(DataSources::LOCATIONS);
        locationKey.push_back('.');
        locationKey.append(location.getName());

        Persistence::DataObjectHandle locationObject = m_dataSystem->getObject(locationKey);
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

    Persistence::DataObjectHandle locationObject = m_dataSystem->getObject(key);
    locationObject.set(Stats::DataSources::IS_DELTA, modifier.getChangeType() == Stats::ChangeType::kDelta);
    locationObject.set(Stats::DataSources::AMOUNT, modifier.getAmount());
  }
}