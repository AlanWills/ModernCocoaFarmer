#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Events/Event.h"


namespace MCF::Stats
{
  class Modifier;
}

namespace MCF::Family
{
  class Child : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(Child, MCFLibraryDllExport)

    public:
      float getHealth() const { return m_health.getValue(); }
      void setHealth(float health) const { return m_health.setValue(health); }

      float getSafety() const { return m_safety.getValue(); }
      void setSafety(float safety) { m_safety.setValue(safety); }

      float getEducation() const { return m_education.getValue(); }
      void setEducation(float education) { m_education.setValue(education); }

      float getHappiness() const { return m_happiness.getValue(); }
      void setHappiness(float happiness) { m_happiness.setValue(happiness); }

      MCFLibraryDllExport void applyHealthModifier(const Stats::Modifier& modifier);
      MCFLibraryDllExport void applyEducationModifier(const Stats::Modifier& modifier);
      MCFLibraryDllExport void applySafetyModifier(const Stats::Modifier& modifier);
      MCFLibraryDllExport void applyHappinessModifier(const Stats::Modifier& modifier);

      bool isAtLocation() const { return !m_currentLocation.empty(); }
      const std::string& getCurrentLocation() const { return m_currentLocation; }
      void setCurrentLocation(const std::string& currentLocation) { m_currentLocation = currentLocation; }

      bool isSelected() const { return m_isSelected; }
      void setSelected(bool isSelected) { m_isSelected = isSelected; }

      static const char* const HEALTH_FIELD_NAME;
      static const char* const SAFETY_FIELD_NAME;
      static const char* const EDUCATION_FIELD_NAME;
      static const char* const HAPPINESS_FIELD_NAME;

    private:
      void applyModifier(const Stats::Modifier& modifier, Celeste::ValueField<float>& attributeToModify);

      Celeste::ValueField<float>& m_health;
      Celeste::ValueField<float>& m_safety;
      Celeste::ValueField<float>& m_education;
      Celeste::ValueField<float>& m_happiness;
      
      std::string m_currentLocation;
      bool m_isSelected;
  };
}