#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Memory/ObserverPtr.h"
#include "UID/StringId.h"


namespace CelesteEngine
{
  class EventArgs;
}

namespace MCF::Time
{
  class TimeManager;
}

namespace MCF::Family
{
  class FamilyManager;
  class Child;
}

namespace MCF::Buildings
{
  class BuildingInformation;

  class BuildingsManager : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(BuildingsManager, MCFLibraryDllExport);

    public:
      void setTimeManager(observer_ptr<Time::TimeManager> timeManager);
      void setFamilyManager(observer_ptr<Family::FamilyManager> familyManager);

      void sendChildToBuilding(BuildingInformation& buildingInformation, Family::Child& child);

      static const char* const BUILDINGS_ELEMENT_NAME;
      static const char* const BUILDING_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      using BuildingsInformation = std::unordered_map<std::string, std::unique_ptr<BuildingInformation>>;

      void onDayPassed(CelesteEngine::EventArgs& e);

      observer_ptr<Time::TimeManager> m_timeManager;
      observer_ptr<Family::FamilyManager> m_familyManager;
      BuildingsInformation m_buildingsInformation;

      CelesteEngine::StringId m_onDayPassedHandle;
  };
}