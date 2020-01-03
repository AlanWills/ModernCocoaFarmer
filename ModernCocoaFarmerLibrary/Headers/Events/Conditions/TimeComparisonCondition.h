#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Conditions/ICondition.h"

// Day/Month/Year enum
// Operator enum
// Value int

namespace MCF::Events::Conditions
{
  class TimeComparisonCondition : public ICondition
  {
    DECLARE_SCRIPTABLE_OBJECT(TimeComparisonCondition, MCFLibraryDllExport);

    public:
      enum class Period
      {
        kDay,
        kMonth,
        kYear
      };

      enum class Operator
      {
        kLessThan,
        kLessThanOrEqualTo,
        kEqual,
        kGreaterThanOrEqualTo,
        kGreaterThan
      };

    private:
      CelesteEngine::ValueField<Period>& m_period;
      CelesteEngine::ValueField<Operator>& m_operator;
      CelesteEngine::ValueField<int>& m_value;
  };
}