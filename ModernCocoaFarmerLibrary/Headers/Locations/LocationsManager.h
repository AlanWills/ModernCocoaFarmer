#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Memory/ObserverPtr.h"
#include "UID/StringId.h"


namespace CelesteEngine
{
  struct EventArgs;
}

namespace MCF::Time
{
  class TimeManager;
}

namespace MCF::Family
{
  class Child;
}

namespace MCF::Locations
{
  class Location;

  class LocationsManager : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(LocationsManager, MCFLibraryDllExport);

    private:
      using LocationsInformation = std::unordered_map<std::string, std::unique_ptr<Location>>;

    public:
      size_t getNumLocations() const { return m_locations.size(); }
      observer_ptr<Location> getLocation(const std::string& locationName);

      void setTimeManager(observer_ptr<Time::TimeManager> timeManager);
      void sendChildToLocation(Location& locationInformation, Family::Child& child);

      static const char* const LOCATIONS_ELEMENT_NAME;
      static const char* const LOCATION_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      void onDayPassed();

      observer_ptr<Time::TimeManager> m_timeManager;
      LocationsInformation m_locations;

      CelesteEngine::StringId m_onDayPassedHandle;
  };
}