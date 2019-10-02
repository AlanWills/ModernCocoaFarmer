#pragma once

#include "Objects/ScriptableObject.h"
#include "MCFLibraryDllExport.h"
#include "Stats/ChildModifier.h"


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
        const Stats::ChildModifier& getHealthModifier() const { return m_healthModifier; }
        const Stats::ChildModifier& getSafetyModifier() const { return m_safetyModifier; }
        const Stats::ChildModifier& getEducationModifier() const { return m_educationModifier; }
        const Stats::ChildModifier& getHappinessModifier() const { return m_happinessModifier; }
        const Stats::Modifier& getMoneyModifier() const { return m_moneyModifier; }
        float getMonthsToComplete() const { return m_monthsToComplete.getValue(); }

        static const std::string DESCRIPTION_FIELD_NAME;
        static const std::string HEALTH_MODIFIER_FIELD_NAME;
        static const std::string SAFETY_MODIFIER_FIELD_NAME;
        static const std::string EDUCATION_MODIFIER_FIELD_NAME;
        static const std::string HAPPINESS_MODIFIER_FIELD_NAME;
        static const std::string MONEY_MODIFIER_FIELD_NAME;
        static const std::string MONTHS_TO_COMPLETE_FIELD_NAME;

      private:
        CelesteEngine::ReferenceField<std::string>& m_description;
        Stats::ChildModifier& m_healthModifier;
        Stats::ChildModifier& m_safetyModifier;
        Stats::ChildModifier& m_educationModifier;
        Stats::ChildModifier& m_happinessModifier;
        Stats::Modifier& m_moneyModifier;
        CelesteEngine::ValueField<float>& m_monthsToComplete;
    };
  }
}