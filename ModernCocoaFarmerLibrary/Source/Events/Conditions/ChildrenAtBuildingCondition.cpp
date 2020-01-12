#include "Events/Conditions/ChildrenAtBuildingCondition.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Deserialization/Logic/LogicDeserializers.h"
#include "Family/FamilyManager.h"


namespace MCF::Events::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(ChildrenAtBuildingCondition);

  //------------------------------------------------------------------------------------------------
  const char* const ChildrenAtBuildingCondition::NUMBER_OF_CHILDREN_ATTRIBUTE_NAME = "number_of_children";
  const char* const ChildrenAtBuildingCondition::CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME = "children_comparison_operator";
  const char* const ChildrenAtBuildingCondition::BUILDING_ATTRIBUTE_NAME = "building";

  //------------------------------------------------------------------------------------------------
  ChildrenAtBuildingCondition::ChildrenAtBuildingCondition() :
    m_numberOfChildren(createValueField<size_t>(NUMBER_OF_CHILDREN_ATTRIBUTE_NAME)),
    m_childrenComparisonOperator(createValueField<Logic::ComparisonOperator>(CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_building(createReferenceField<std::string>(BUILDING_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool ChildrenAtBuildingCondition::isConditionMet(
    Time::TimeManager&,
    Money::MoneyManager&,
    Family::FamilyManager& familyManager) const
  {
    ASSERT_FAIL_MSG("TODO");
    return Logic::isComparisonTrue(
      familyManager.getChildCount(), 
      getNumberOfChildren(), 
      getChildrenComparisonOperator());
  }
}