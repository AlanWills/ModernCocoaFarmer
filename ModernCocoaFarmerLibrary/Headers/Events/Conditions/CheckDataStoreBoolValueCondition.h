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

      const std::string& getValueName() const { return m_valueName.getValue(); }
      void setValueName(const std::string& valueName) { return m_valueName.setValue(valueName); }

      Logic::ComparisonOperator getComparisonOperator() const { return m_comparisonOperator.getValue(); }
      void setComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_comparisonOperator.setValue(comparisonOperator); }

      bool getExpectedValue() const { return m_expectedValue.getValue(); }
      void setExpectedValue(bool expectedValue) { m_expectedValue.setValue(expectedValue); }

      bool getDefaultValue() const { return m_defaultValue.getValue(); }
      void setDefaultValue(bool defaultValue) { m_defaultValue.setValue(defaultValue); }

      bool isConditionMet(
        Time::TimeManager& timeManager,
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const override;

      static const char* const DATA_STORE_PATH_ATTRIBUTE_NAME;
      static const char* const VALUE_NAME_ATTRIBUTE_NAME;
      static const char* const COMPARISON_OPERATOR_ATTRIBUTE_NAME;
      static const char* const EXPECTED_VALUE_ATTRIBUTE_NAME;
      static const char* const DEFAULT_VALUE_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ReferenceField<std::string>& m_dataStorePath;
      CelesteEngine::ReferenceField<std::string>& m_valueName;
      CelesteEngine::ValueField<Logic::ComparisonOperator>& m_comparisonOperator;
      CelesteEngine::ValueField<bool>& m_expectedValue;
      CelesteEngine::ValueField<bool>& m_defaultValue;
  };
}