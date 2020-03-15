#include "Events/Conditions/ChildrenAtLocation.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Deserialization/Logic/LogicDeserializers.h"
#include "Family/FamilyManager.h"


namespace MCF::Events::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(ChildrenAtLocation);

  //------------------------------------------------------------------------------------------------
  const char* const ChildrenAtLocation::NUMBER_OF_CHILDREN_ATTRIBUTE_NAME = "number_of_children";
  const char* const ChildrenAtLocation::CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME = "children_comparison_operator";
  const char* const ChildrenAtLocation::LOCATION_ATTRIBUTE_NAME = "location";

  //------------------------------------------------------------------------------------------------
  ChildrenAtLocation::ChildrenAtLocation() :
    m_numberOfChildren(createValueField<size_t>(NUMBER_OF_CHILDREN_ATTRIBUTE_NAME)),
    m_childrenComparisonOperator(createValueField<Logic::ComparisonOperator>(CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_location(createReferenceField<std::string>(LOCATION_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool ChildrenAtLocation::isConditionMet(
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