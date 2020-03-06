#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Conditions/Condition.h"
#include "Logic/ComparisonOperator.h"


namespace MCF::Events::Conditions
{
  class RandomNumberComparisonCondition : public Condition
  {
    DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(RandomNumberComparisonCondition, MCFLibraryDllExport);

    public:
      Logic::ComparisonOperator getComparisonOperator() const { return m_comparisonOperator.getValue(); }
      void setComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_comparisonOperator.setValue(comparisonOperator); }

      float getValue() const { return m_value.getValue(); }
      void setValue(float value) { m_value.setValue(value); }

      bool isConditionMet(
        Time::TimeManager& timeManager,
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const override;

      static const char* const COMPARISON_OPERATOR_ATTRIBUTE_NAME;
      static const char* const VALUE_ATTRIBUTE_NAME;

    private:
      Celeste::ValueField<Logic::ComparisonOperator>& m_comparisonOperator;
      Celeste::ValueField<float>& m_value;
  };
}