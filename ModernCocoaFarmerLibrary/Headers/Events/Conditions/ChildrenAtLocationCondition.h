#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Conditions/Condition.h"
#include "Logic/ComparisonOperator.h"


namespace MCF::Events::Conditions
{
  class ChildrenAtLocationCondition : public Condition
  {
    DECLARE_SCRIPTABLE_OBJECT(ChildrenAtLocationCondition, MCFLibraryDllExport);

    public:
      size_t getNumberOfChildren() const { return m_numberOfChildren.getValue(); }
      void setNumberOfChildren(size_t numberOfChildren) { m_numberOfChildren.setValue(numberOfChildren); }

      Logic::ComparisonOperator getChildrenComparisonOperator() const { return m_childrenComparisonOperator.getValue(); }
      void setChildrenComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_childrenComparisonOperator.setValue(comparisonOperator); }

      const std::string& getLocation() const { return m_location.getValue(); }
      void setLocation(const std::string& location) { m_location.setValue(location); }

      bool isConditionMet(
        Time::TimeManager& timeManager,
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const override;

      static const char* const NUMBER_OF_CHILDREN_ATTRIBUTE_NAME;
      static const char* const CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME;
      static const char* const LOCATION_ATTRIBUTE_NAME;

    private:
      Celeste::ValueField<size_t>& m_numberOfChildren;
      Celeste::ValueField<Logic::ComparisonOperator>& m_childrenComparisonOperator;
      Celeste::ReferenceField<std::string>& m_location;
  };
}