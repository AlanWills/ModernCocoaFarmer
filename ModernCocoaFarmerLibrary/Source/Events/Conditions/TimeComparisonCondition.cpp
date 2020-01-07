#include "Events/Conditions/TimeComparisonCondition.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Time/TimeManager.h"
#include "Deserialization/Time/TimeDeserializers.h"
#include "Deserialization/Logic/LogicDeserializers.h"


namespace MCF::Events::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(TimeComparisonCondition);

  //------------------------------------------------------------------------------------------------
  const char* const TimeComparisonCondition::TIME_PERIOD_ATTRIBUTE_NAME = "time_period";
  const char* const TimeComparisonCondition::COMPARISON_OPERATOR_ATTRIBUTE_NAME = "comparison_operator";
  const char* const TimeComparisonCondition::VALUE_ATTRIBUTE_NAME = "value";

  //------------------------------------------------------------------------------------------------
  TimeComparisonCondition::TimeComparisonCondition() :
    m_timeToCheck(createValueField<Time::TimePeriod>(TIME_PERIOD_ATTRIBUTE_NAME, Time::TimePeriod::kMonth)),
    m_comparisonOperator(createValueField<Logic::ComparisonOperator>(COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_value(createValueField<int>(VALUE_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool TimeComparisonCondition::isConditionMet(
    Time::TimeManager& timeManager,
    Money::MoneyManager&,
    Family::FamilyManager&) const
  {
    switch (getTimeToCheck())
    {
    case Time::TimePeriod::kDay:
      return check(timeManager.getCurrentDay());

    case Time::TimePeriod::kMonth:
      return check(timeManager.getCurrentMonth());

    case Time::TimePeriod::kYear:
      return check(timeManager.getCurrentYear());

    default:
      ASSERT_FAIL();
      return false;
    }
  }

  //------------------------------------------------------------------------------------------------
  bool TimeComparisonCondition::check(size_t currentTimePeriod) const
  {
    switch (getComparisonOperator())
    {
    case Logic::ComparisonOperator::kLessThan:
      return getValue() < currentTimePeriod;

    case Logic::ComparisonOperator::kLessThanOrEqualTo:
      return getValue() <= currentTimePeriod;

    case Logic::ComparisonOperator::kEqual:
      return getValue() == currentTimePeriod;

    case Logic::ComparisonOperator::kGreaterThanOrEqualTo:
      return getValue() >= currentTimePeriod;

    case Logic::ComparisonOperator::kGreaterThan:
      return getValue() > currentTimePeriod;

    default:
      ASSERT_FAIL();
      return false;
    }
  }
}