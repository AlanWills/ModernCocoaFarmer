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
  class Child : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(Child, MCFLibraryDllExport)

    public:
      using OnSelectedChangedEvent = CelesteEngine::Event<Child&>;

      float getHealth() const { return m_health.getValue(); }
      void setHealth(float health) const { return m_health.setValue(health); }

      float getSafety() const { return m_safety.getValue(); }
      void setSafety(float safety) { m_safety.setValue(safety); }

      float getEducation() const { return m_education.getValue(); }
      void setEducation(float education) { m_education.setValue(education); }

      float getHappiness() const { return m_happiness.getValue(); }
      void setHappiness(float happiness) { m_happiness.setValue(happiness); }

      void applyHealthModifier(Stats::Modifier& modifier);
      void applyEducationModifier(Stats::Modifier& modifier);
      void applySafetyModifier(Stats::Modifier& modifier);
      void applyHappinessModifier(Stats::Modifier& modifier);

      bool isAtBuilding() const { return !m_currentBuilding.empty(); }
      const std::string& getCurrentBuilding() const { return m_currentBuilding; }
      void setCurrentBuilding(const std::string& currentBuilding) { m_currentBuilding = currentBuilding; }

      bool isSelected() const { return m_isSelected; }
      void setSelected(bool isSelected);

      const OnSelectedChangedEvent& getOnSelectedChangedEvent() const { return m_onSelectedChanged; }

      static const char* const HEALTH_FIELD_NAME;
      static const char* const SAFETY_FIELD_NAME;
      static const char* const EDUCATION_FIELD_NAME;
      static const char* const HAPPINESS_FIELD_NAME;

    private:
      void applyModifier(Stats::Modifier& modifier, CelesteEngine::ValueField<float>& attributeToModify);
      void applyInstantModifier(Stats::Modifier& modifier, CelesteEngine::ValueField<float>& attributeToModify);
      void applyPeriodicModifier(Stats::Modifier& modifier, CelesteEngine::ValueField<float>& attributeToModify);

      CelesteEngine::ValueField<float>& m_health;
      CelesteEngine::ValueField<float>& m_safety;
      CelesteEngine::ValueField<float>& m_education;
      CelesteEngine::ValueField<float>& m_happiness;
      
      std::string m_currentBuilding;

      bool m_isSelected;
      OnSelectedChangedEvent m_onSelectedChanged;
  };
}