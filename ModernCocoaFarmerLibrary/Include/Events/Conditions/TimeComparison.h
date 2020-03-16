#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Conditions/Condition.h"
#include "Time/TimePeriod.h"
#include "Logic/ComparisonOperator.h"


namespace MCF::Events::Conditions
{
  class TimeComparison : public Condition
  {
    DECLARE_SCRIPTABLE_OBJECT(TimeComparison, MCFLibraryDllExport);

    public:
      inline Time::TimePeriod getTimeToCheck() const { return m_timeToCheck.getValue(); }
      inline void setTimeToCheck(Time::TimePeriod timePeriod) { m_timeToCheck.setValue(timePeriod); }

      inline Logic::ComparisonOperator getComparisonOperator() const { return m_comparisonOperator.getValue(); }
      inline void setComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_comparisonOperator.setValue(comparisonOperator); }

      inline size_t getValue() const { return m_value.getValue(); }
      inline void setValue(size_t value) { m_value.setValue(value); }

      bool isConditionMet(
        Time::TimeManager& timeManager,
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const override;

      static const char* const TIME_PERIOD_ATTRIBUTE_NAME;
      static const char* const COMPARISON_OPERATOR_ATTRIBUTE_NAME;
      static const char* const VALUE_ATTRIBUTE_NAME;

    private:
      bool check(size_t currentTimePeriod) const;

      Celeste::ValueField<Time::TimePeriod>& m_timeToCheck;
      Celeste::ValueField<Logic::ComparisonOperator>& m_comparisonOperator;
      Celeste::ValueField<size_t>& m_value;
  };
}