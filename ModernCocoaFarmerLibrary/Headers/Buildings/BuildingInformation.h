#pragma once

#include "Objects/ScriptableObject.h"
#include "MCFLibraryDllExport.h"
#include "Stats/Modifier.h"


namespace MCF
{
  namespace Stats
  {
    class Modifier;
  }

  namespace Buildings
  {
    class MCFLibraryDllExport BuildingInformation : public CelesteEngine::ScriptableObject
    {
      DECLARE_SCRIPTABLE_OBJECT(BuildingInformation)

      public:
        const std::string& getDescription() const { return m_description.getValue(); }
        const Stats::Modifier& getHealthModifier() const { return m_healthModifier.getValue(); }
        const Stats::Modifier& getSafetyModifier() const { return m_safetyModifier.getValue(); }
        const Stats::Modifier& getEducationModifier() const { return m_educationModifier.getValue(); }
        const Stats::Modifier& getHappinessModifier() const { return m_happinessModifier.getValue(); }
        const Stats::Modifier& getCostModifier() const { return m_costModifier.getValue(); }
        float getMonthsToComplete() const { return m_monthsToComplete.getValue(); }

        static const std::string DESCRIPTION_FIELD_NAME;
        static const std::string HEALTH_MODIFIER_FIELD_NAME;
        static const std::string SAFETY_MODIFIER_FIELD_NAME;
        static const std::string EDUCATION_MODIFIER_FIELD_NAME;
        static const std::string HAPPINESS_MODIFIER_FIELD_NAME;
        static const std::string COST_MODIFIER_FIELD_NAME;
        static const std::string MONTHS_TO_COMPLETE_FIELD_NAME;

      private:
        CelesteEngine::ReferenceField<std::string>& m_description;
        CelesteEngine::ReferenceField<Stats::Modifier>& m_healthModifier;
        CelesteEngine::ReferenceField<Stats::Modifier>& m_safetyModifier;
        CelesteEngine::ReferenceField<Stats::Modifier>& m_educationModifier;
        CelesteEngine::ReferenceField<Stats::Modifier>& m_happinessModifier;
        CelesteEngine::ReferenceField<Stats::Modifier>& m_costModifier;
        CelesteEngine::ValueField<float>& m_monthsToComplete;
    };
  }
}