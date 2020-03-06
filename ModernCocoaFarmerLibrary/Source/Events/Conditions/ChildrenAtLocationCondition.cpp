#include "Events/Conditions/ChildrenAtLocationCondition.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Deserialization/Logic/LogicDeserializers.h"
#include "Family/FamilyManager.h"


namespace MCF::Events::Conditions
{
  REGISTER_UNMANAGED_COMPONENTABLE_OBJECT(ChildrenAtLocationCondition);

  //------------------------------------------------------------------------------------------------
  const char* const ChildrenAtLocationCondition::NUMBER_OF_CHILDREN_ATTRIBUTE_NAME = "number_of_children";
  const char* const ChildrenAtLocationCondition::CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME = "children_comparison_operator";
  const char* const ChildrenAtLocationCondition::LOCATION_ATTRIBUTE_NAME = "location";

  //------------------------------------------------------------------------------------------------
  ChildrenAtLocationCondition::ChildrenAtLocationCondition() :
    m_numberOfChildren(createValueField<size_t>(NUMBER_OF_CHILDREN_ATTRIBUTE_NAME)),
    m_childrenComparisonOperator(createValueField<Logic::ComparisonOperator>(CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_location(createReferenceField<std::string>(LOCATION_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool ChildrenAtLocationCondition::isConditionMet(
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