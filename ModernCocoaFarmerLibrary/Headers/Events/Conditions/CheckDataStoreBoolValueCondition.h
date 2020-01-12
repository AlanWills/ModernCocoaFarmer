#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Conditions/Condition.h"
#include "Logic/ComparisonOperator.h"


namespace MCF::Events::Conditions
{
  class CheckDataStoreBoolValueCondition : public Condition
  {
    DECLARE_SCRIPTABLE_OBJECT(CheckDataStoreBoolValueCondition, MCFLibraryDllExport);

    public:
      const std::string& getDataStorePath() const { return m_dataStorePath.getValue(); }
      void setDataStorePath(const std::string& dataStorePath) { return m_dataStorePath.setValue(dataStorePath); }

      Logic::ComparisonOperator getComparisonOperator() const { return m_comparisonOperator.getValue(); }
      void setComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_comparisonOperator.setValue(comparisonOperator); }

      bool getValue() const { return m_value.getValue(); }
      void setValue(bool value) { m_value.setValue(value); }

      bool isConditionMet(
        Time::TimeManager& timeManager,
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const override;

      static const char* const DATA_STORE_PATH_ATTRIBUTE_NAME;
      static const char* const COMPARISON_OPERATOR_ATTRIBUTE_NAME;
      static const char* const VALUE_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ReferenceField<std::string> m_dataStorePath;
      CelesteEngine::ValueField<Logic::ComparisonOperator>& m_comparisonOperator;
      CelesteEngine::ValueField<bool>& m_value;
  };
}