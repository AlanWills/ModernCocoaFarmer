#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Conditions/Condition.h"
#include "Logic/ComparisonOperator.h"


namespace MCF::Events::Conditions
{
  class ChildrenStatComparisonCondition : public Condition
  {
    DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(ChildrenStatComparisonCondition, MCFLibraryDllExport);

  public:
    size_t getNumberOfChildren() const { return m_numberOfChildren.getValue(); }
    void setNumberOfChildren(size_t numberOfChildren) { m_numberOfChildren.setValue(numberOfChildren); }

    Logic::ComparisonOperator getChildrenComparisonOperator() const { return m_childrenComparisonOperator.getValue(); }
    void setChildrenComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_childrenComparisonOperator.setValue(comparisonOperator); }

    const std::string& getStat() const { return m_stat.getValue(); }
    void setStat(const std::string& location) { m_stat.setValue(location); }

    float getValue() const { return m_value.getValue(); }
    void setValue(float value) { m_value.setValue(value); }

    Logic::ComparisonOperator getStatComparisonOperator() const { return m_statComparisonOperator.getValue(); }
    void setStatComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_statComparisonOperator.setValue(comparisonOperator); }

    bool isConditionMet(
      Time::TimeManager& timeManager,
      Money::MoneyManager& moneyManager,
      Family::FamilyManager& familyManager) const override;

    static const char* const NUMBER_OF_CHILDREN_ATTRIBUTE_NAME;
    static const char* const CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME;
    static const char* const STAT_ATTRIBUTE_NAME;
    static const char* const VALUE_ATTRIBUTE_NAME;
    static const char* const STAT_COMPARISON_OPERATOR_ATTRIBUTE_NAME;

  private:
    Celeste::ValueField<size_t>& m_numberOfChildren;
    Celeste::ValueField<Logic::ComparisonOperator>& m_childrenComparisonOperator;
    Celeste::ReferenceField<std::string>& m_stat;
    Celeste::ValueField<float>& m_value;
    Celeste::ValueField<Logic::ComparisonOperator>& m_statComparisonOperator;
  };
}