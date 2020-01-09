#pragma once

#include "MCFLibraryDllExport.h"
#include "Events/Conditions/Condition.h"
#include "Logic/ComparisonOperator.h"


namespace MCF::Events::Conditions
{
  class ChildrenAtBuildingCondition : public Condition
  {
    DECLARE_SCRIPTABLE_OBJECT(ChildrenAtBuildingCondition, MCFLibraryDllExport);

    public:
      int getNumberOfChildren() const { return m_numberOfChildren.getValue(); }
      void setNumberOfChildren(int numberOfChildren) { m_numberOfChildren.setValue(numberOfChildren); }

      Logic::ComparisonOperator getComparisonOperator() const { return m_comparisonOperator.getValue(); }
      void setComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_comparisonOperator.setValue(comparisonOperator); }

      const std::string& getBuilding() const { return m_building.getValue(); }
      void setBuilding(const std::string& building) { m_building.setValue(building); }

      bool isConditionMet(
        Time::TimeManager& timeManager,
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const override;

      static const char* const NUMBER_OF_CHILDREN_ATTRIBUTE_NAME;
      static const char* const COMPARISON_OPERATOR_ATTRIBUTE_NAME;
      static const char* const BUILDING_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ValueField<int>& m_numberOfChildren;
      CelesteEngine::ValueField<Logic::ComparisonOperator>& m_comparisonOperator;
      CelesteEngine::ReferenceField<std::string> m_building;
  };
}