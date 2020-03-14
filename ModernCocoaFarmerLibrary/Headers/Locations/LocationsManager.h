#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Memory/ObserverPtr.h"
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

namespace MCF::Locations
{
  class Location;

  class LocationsManager : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(LocationsManager, MCFLibraryDllExport);

    private:
      using LocationsInformation = std::unordered_map<std::string, std::unique_ptr<Location>>;

    public:
      size_t getNumLocations() const { return m_locations.size(); }
      observer_ptr<Location> getLocation(const std::string& locationName);

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
      LocationsInformation m_locations;
  };
}