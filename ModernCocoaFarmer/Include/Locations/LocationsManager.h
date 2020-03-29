#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Memory/ObserverPtr.h"
#include "Events/Event.h"
#include "UID/StringId.h"


namespace MCF::Time
{
  class TimeManager;
}

namespace MCF::Money
{
  class MoneyManager;
}

namespace MCF::Family
{
  class Child;
  class FamilyManager;
}

namespace MCF::Notifications
{
  class NotificationManager;
}

namespace MCF::Persistence
{
  class DataStore;
}

namespace MCF::Stats
{
  class Modifier;
}

namespace MCF::Locations
{
  class Location;

  class LocationsManager : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(LocationsManager, MCFLibraryDllExport);

    private:
      using LocationsInformation = std::unordered_map<std::string, std::unique_ptr<Location>>;

    public:
      using LocationActivatedEvent = Celeste::Event<Location&>;

      void setDataStore(observer_ptr<Persistence::DataStore> dataStore);

      size_t getNumLocations() const { return m_locations.size(); }
      observer_ptr<Location> findLocation(const std::string& locationName) const;

      const LocationActivatedEvent& getOnLocationActivatedEvent() const { return m_onLocationActivatedEvent; }

      void activateLocation(Location& location);
      void onDayPassed();

      void checkLocationsForChildrenArriving(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Notifications::NotificationManager& notificationManager);

      void checkLocationsForChildrenLeaving(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Notifications::NotificationManager& notificationManager);

      static const char* const LOCATIONS_ELEMENT_NAME;
      static const char* const LOCATION_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      void updateDataStore();
      void writeModifier(const std::string& locationKey, const char* const modifierKey, const Stats::Modifier& modifier);
      
      bool m_suspendDataStoreUpdates = false;
      observer_ptr<Persistence::DataStore> m_dataStore = nullptr;

      LocationsInformation m_locations;
      LocationActivatedEvent m_onLocationActivatedEvent;
  };
}