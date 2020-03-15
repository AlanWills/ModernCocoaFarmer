#include "Events/Conditions/ChildrenStatComparison.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Deserialization/Logic/LogicDeserializers.h"
#include "Family/FamilyManager.h"
#include "Family/Child.h"


namespace MCF::Events::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(ChildrenStatComparison);

  //------------------------------------------------------------------------------------------------
  const char* const ChildrenStatComparison::NUMBER_OF_CHILDREN_ATTRIBUTE_NAME = "number_of_children";
  const char* const ChildrenStatComparison::CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME = "children_comparison_operator";
  const char* const ChildrenStatComparison::STAT_ATTRIBUTE_NAME = "stat";
  const char* const ChildrenStatComparison::VALUE_ATTRIBUTE_NAME = "value";
  const char* const ChildrenStatComparison::STAT_COMPARISON_OPERATOR_ATTRIBUTE_NAME = "stat_comparison_operator";

  //------------------------------------------------------------------------------------------------
  ChildrenStatComparison::ChildrenStatComparison() :
    m_numberOfChildren(createValueField<size_t>(NUMBER_OF_CHILDREN_ATTRIBUTE_NAME)),
    m_childrenComparisonOperator(createValueField<Logic::ComparisonOperator>(CHILDREN_COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_stat(createReferenceField<std::string>(STAT_ATTRIBUTE_NAME)),
    m_value(createValueField<float>(VALUE_ATTRIBUTE_NAME)),
    m_statComparisonOperator(createValueField<Logic::ComparisonOperator>(STAT_COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool ChildrenStatComparison::isConditionMet(
    Time::TimeManager&,
    Money::MoneyManager&,
    Family::FamilyManager& familyManager) const
  {
    size_t numOfMatchingChildren = 0;

    for (const auto& child : familyManager)
    {
      float currentValue = 0;

      if (getStat() == Family::Child::HEALTH_FIELD_NAME)
      {
        currentValue = child->getHealth();
      }
      else if (getStat() == Family::Child::EDUCATION_FIELD_NAME)
      {
        currentValue = child->getEducation();
      }
      else if (getStat() == Family::Child::HAPPINESS_FIELD_NAME)
      {
        currentValue = child->getHappiness();
      }
      else if (getStat() == Family::Child::SAFETY_FIELD_NAME)
      {
        currentValue = child->getSafety();
      }
      else
      {
        ASSERT_FAIL();
        continue;
      }

      if (Logic::isComparisonTrue(currentValue, getValue(), getStatComparisonOperator()))
      {
        ++numOfMatchingChildren;
      }
    }

    return Logic::isComparisonTrue(
      numOfMatchingChildren,
      getNumberOfChildren(),
      getChildrenComparisonOperator());
  }
}