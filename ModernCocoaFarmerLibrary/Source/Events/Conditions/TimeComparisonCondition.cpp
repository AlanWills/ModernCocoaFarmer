#include "Events/Conditions/TimeComparisonCondition.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Time/TimeManager.h"
#include "Deserialization/Time/TimeDeserializers.h"
#include "Deserialization/Logic/LogicDeserializers.h"


namespace MCF::Events::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(TimeComparisonCondition);

  //------------------------------------------------------------------------------------------------
  TimeComparisonCondition::TimeComparisonCondition() :
    m_timeToCheck(createValueField<Time::TimePeriod>("time_period", Time::TimePeriod::kMonth)),
    m_comparisonOperator(createValueField<Logic::ComparisonOperator>("comparison_operator", Logic::ComparisonOperator::kEqual)),
    m_value(createValueField<int>("value"))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool TimeComparisonCondition::isConditionMet(Time::TimeManager& timeManager) const
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