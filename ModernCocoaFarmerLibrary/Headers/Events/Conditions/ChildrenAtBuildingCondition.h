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
      size_t getNumberOfChildren() const { return m_numberOfChildren.getValue(); }
      void setNumberOfChildren(size_t numberOfChildren) { m_numberOfChildren.setValue(numberOfChildren); }

      Logic::ComparisonOperator getChildrenComparisonOperator() const { return m_childrenComparisonOperator.getValue(); }
      void setChildrenComparisonOperator(Logic::ComparisonOperator comparisonOperator) { m_childrenComparisonOperator.setValue(comparisonOperator); }

      const std::string& getBuilding() const { return m_building.getValue(); }
      void setBuilding(const std::string& building) { m_building.setValue(building); }

      bool isConditionMet(
        Time::TimeManager& timeManager,
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const override;

      static const char* const NUMBER_OF_CHILDREN_ATTRIBUTE_NAME;
      static const char* const CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME;
      static const char* const BUILDING_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ValueField<size_t>& m_numberOfChildren;
      CelesteEngine::ValueField<Logic::ComparisonOperator>& m_childrenComparisonOperator;
      CelesteEngine::ReferenceField<std::string>& m_building;
  };
}