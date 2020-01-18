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

namespace MCF::Buildings
{
  class Building;

  class BuildingsManager : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(BuildingsManager, MCFLibraryDllExport);

    private:
      using BuildingsInformation = std::unordered_map<std::string, std::unique_ptr<Building>>;

    public:
      size_t getNumBuildings() const { return m_buildings.size(); }
      observer_ptr<Building> getBuilding(const std::string& buildingName);

      void setTimeManager(observer_ptr<Time::TimeManager> timeManager);
      void sendChildToBuilding(Building& buildingInformation, Family::Child& child);

      static const char* const BUILDINGS_ELEMENT_NAME;
      static const char* const BUILDING_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      void onDayPassed();

      observer_ptr<Time::TimeManager> m_timeManager;
      BuildingsInformation m_buildings;

      CelesteEngine::StringId m_onDayPassedHandle;
  };
}