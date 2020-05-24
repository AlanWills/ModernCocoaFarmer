#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Family/ChildState.h"


namespace MCF::Stats
{
  class Modifier;
}

namespace MCF::Persistence
{
  class DataObjectHandle;
}

namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Family
{
  class Child : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(Child, MCFLibraryDllExport)

    public:
      float getHealth() const { return m_health.getValue(); }
      MCFLibraryDllExport void setHealth(float health);

      float getSafety() const { return m_safety.getValue(); }
      MCFLibraryDllExport void setSafety(float safety);

      float getEducation() const { return m_education.getValue(); }
      MCFLibraryDllExport void setEducation(float education);

      float getHappiness() const { return m_happiness.getValue(); }
      MCFLibraryDllExport void setHappiness(float happiness);
      
      const std::string& getCurrentLocation() const { return m_currentLocation.getValue(); }
      MCFLibraryDllExport void setCurrentLocation(const std::string& currentLocation);
      bool isAtLocation() const { return !getCurrentLocation().empty(); }

      float getTimeAtLocation() const { return m_timeAtLocation.getValue(); }
      MCFLibraryDllExport void setTimeAtLocation(float timeAtLocation);
      void incrementTimeAtLocation(float increment) { setTimeAtLocation(m_timeAtLocation.getValue() + increment); }

      bool isNotBorn() const { return getState() == ChildState::kNotBorn; }

      bool canActivate() const { return getState() == ChildState::kNotBorn; }
      bool isActivated() const { return getState() == ChildState::kActive; }
      void activate();

      MCFLibraryDllExport bool canGraduate() const;
      bool isGraduated() const { return getState() == ChildState::kGraduated; }
      MCFLibraryDllExport void graduate();

      bool canDie() const { return getHealth() <= 0; }
      bool isDead() const { return getState() == ChildState::kDead; }
      MCFLibraryDllExport void die();

      bool isSelected() const { return m_isSelected; }
      MCFLibraryDllExport void setSelected(bool isSelected);

      MCFLibraryDllExport void applyHealthModifier(const Stats::Modifier& modifier);
      MCFLibraryDllExport void applyEducationModifier(const Stats::Modifier& modifier);
      MCFLibraryDllExport void applySafetyModifier(const Stats::Modifier& modifier);
      MCFLibraryDllExport void applyHappinessModifier(const Stats::Modifier& modifier);

      void setDataSystem(Data::DataSystem& dataSystem);

      static const float MAX_STAT_VALUE;
      static const char* const HEALTH_FIELD_NAME;
      static const char* const SAFETY_FIELD_NAME;
      static const char* const EDUCATION_FIELD_NAME;
      static const char* const HAPPINESS_FIELD_NAME;
      static const char* const CURRENT_LOCATION_FIELD_NAME;
      static const char* const TIME_AT_LOCATION_FIELD_NAME;
      static const char* const STATE_FIELD_NAME;

    private:
      ChildState getState() const { return m_state.getValue(); }

      void setStat(
        float value,
        Celeste::ValueField<float>& attributeToModify,
        const std::string& dataSource);

      void applyModifier(
        const Stats::Modifier& modifier, 
        Celeste::ValueField<float>& attributeToModify, 
        const std::string& dataSource);

      void updateDataObject();

      Celeste::ValueField<float>& m_health;
      Celeste::ValueField<float>& m_safety;
      Celeste::ValueField<float>& m_education;
      Celeste::ValueField<float>& m_happiness;
      Celeste::ReferenceField<std::string>& m_currentLocation;
      Celeste::ValueField<float>& m_timeAtLocation;
      Celeste::ValueField<ChildState>& m_state;

      std::unique_ptr<Persistence::DataObjectHandle> m_dataObjectHandle;
      bool m_isSelected;
  };
}