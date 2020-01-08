#include "Events/Conditions/RandomNumberComparisonCondition.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Time/TimeManager.h"
#include "Deserialization/Logic/LogicDeserializers.h"
#include "Maths/RandomGenerator.h"


namespace MCF::Events::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(RandomNumberComparisonCondition);

  //------------------------------------------------------------------------------------------------
  const char* const RandomNumberComparisonCondition::COMPARISON_OPERATOR_ATTRIBUTE_NAME = "comparison_operator";
  const char* const RandomNumberComparisonCondition::VALUE_ATTRIBUTE_NAME = "value";

  //------------------------------------------------------------------------------------------------
  RandomNumberComparisonCondition::RandomNumberComparisonCondition() :
    m_comparisonOperator(createValueField<Logic::ComparisonOperator>(COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_value(createValueField<float>(VALUE_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool RandomNumberComparisonCondition::isConditionMet(
    Time::TimeManager&,
    Money::MoneyManager&,
    Family::FamilyManager&) const
  {
    float value = CelesteEngine::Random::generate();

    switch (getComparisonOperator())
    {
    case Logic::ComparisonOperator::kLessThan:
      return getValue() < value;

    case Logic::ComparisonOperator::kLessThanOrEqualTo:
      return getValue() <= value;

    case Logic::ComparisonOperator::kEqual:
      return getValue() == value;

    case Logic::ComparisonOperator::kGreaterThanOrEqualTo:
      return getValue() >= value;

    case Logic::ComparisonOperator::kGreaterThan:
      return getValue() > value;

    default:
      ASSERT_FAIL();
      return false;
    }
  }
}