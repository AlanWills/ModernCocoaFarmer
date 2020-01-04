#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Conditions/Condition.h"
#include "Time/TimePeriod.h"
#include "Logic/ComparisonOperator.h"


namespace MCF::Events::Conditions
{
  class TimeComparisonCondition : public Condition
  {
    DECLARE_SCRIPTABLE_OBJECT(TimeComparisonCondition, MCFLibraryDllExport);

    public:
      Time::TimePeriod getTimeToCheck() const { return m_timeToCheck.getValue(); }
      void setTimeToCheck(Time::TimePeriod timePeriod) { m_timeToCheck.setValue(timePeriod); }

      Logic::ComparisonOperator getComparisonOperator() const { return m_comparisonOperator.getValue(); }
      void setComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_comparisonOperator.setValue(comparisonOperator); }

      int getValue() const { return m_value.getValue(); }
      void setValue(int value) { m_value.setValue(value); }

      bool isConditionMet(Time::TimeManager& timeManager) const override;

    private:
      bool check(size_t currentTimePeriod) const;

      CelesteEngine::ValueField<Time::TimePeriod>& m_timeToCheck;
      CelesteEngine::ValueField<Logic::ComparisonOperator>& m_comparisonOperator;
      CelesteEngine::ValueField<int>& m_value;
  };
}