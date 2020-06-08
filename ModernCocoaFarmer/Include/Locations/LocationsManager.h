#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "CelesteStl/Memory/ObserverPtr.h"
#include "Events/Event.h"
#include "UID/StringId.h"


namespace MCF::Data
{
  class DataSystem;
  class ObjectRef;
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
      using LocationsInformation = std::vector<std::reference_wrapper<Location>>;

    public:
      using LocationActivatedEvent = Celeste::Event<Location&>;

      MCFLibraryDllExport void setDataSystem(observer_ptr<Data::DataSystem> dataSystem);

      size_t getNumLocations() const { return m_locations.size(); }
      MCFLibraryDllExport observer_ptr<Location> getLocation(size_t index);
      MCFLibraryDllExport observer_ptr<Location> findLocation(const std::string& locationName) const;

      const LocationActivatedEvent& getOnLocationActivatedEvent() const { return m_onLocationActivatedEvent; }

      MCFLibraryDllExport void activateLocation(Location& location);

      static const char* const LOCATION_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      void updateDataSystem();
      void writeModifier(Data::ObjectRef& locationObject, const char* const modifierKey, const Stats::Modifier& modifier);
      
      observer_ptr<Data::DataSystem> m_dataSystem = nullptr;

      LocationsInformation m_locations;
      LocationActivatedEvent m_onLocationActivatedEvent;
  };
}