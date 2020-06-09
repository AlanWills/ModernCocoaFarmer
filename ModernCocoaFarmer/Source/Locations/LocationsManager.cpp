#include "Locations/LocationsManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Locations/Location.h"
#include "Locations/DataSources.h"
#include "Stats/DataSources.h"
#include "Stats/Modifier.h"
#include "Data/DataSystem.h"
#include "Data/ObjectRef.h"
#include "Persistence/DataPath.h"

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
        
        Data::ObjectRef locationObject(*m_dataSystem, Persistence::DataPath::combine(DataSources::LOCATIONS, location.getName()));
        locationObject.set(DataSources::NAME, location.getName());
        locationObject.set(DataSources::DESCRIPTION, location.getDescription());
        locationObject.set(DataSources::DAYS_TO_COMPLETE, location.getDaysToComplete());

        writeModifier(locationObject, Stats::DataSources::EDUCATION, location.getEducationModifier());
        writeModifier(locationObject, Stats::DataSources::HAPPINESS, location.getHappinessModifier());
        writeModifier(locationObject, Stats::DataSources::HEALTH, location.getHealthModifier());
        writeModifier(locationObject, Stats::DataSources::MONEY, location.getMoneyModifier());
        writeModifier(locationObject, Stats::DataSources::SAFETY, location.getSafetyModifier());
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LocationsManager::writeModifier(
    Data::ObjectRef& locationObject, 
    const char* const modifierKey, 
    const Stats::Modifier& modifier)
  {
    locationObject.set(Persistence::DataPath::combine(modifierKey, Stats::DataSources::IS_DELTA), modifier.getChangeType() == Stats::ChangeType::kDelta);
    locationObject.set(Persistence::DataPath::combine(modifierKey, Stats::DataSources::AMOUNT), modifier.getAmount());
  }
}