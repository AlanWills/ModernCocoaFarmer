#include "Events/Conditions/TimeComparison.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Time/TimeManager.h"
#include "Deserialization/Time/TimeDeserializers.h"
#include "Deserialization/Logic/LogicDeserializers.h"


namespace MCF::Events::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(TimeComparison);

  //------------------------------------------------------------------------------------------------
  const char* const TimeComparison::TIME_PERIOD_ATTRIBUTE_NAME = "time_period";
  const char* const TimeComparison::COMPARISON_OPERATOR_ATTRIBUTE_NAME = "comparison_operator";
  const char* const TimeComparison::VALUE_ATTRIBUTE_NAME = "value";

  //------------------------------------------------------------------------------------------------
  TimeComparison::TimeComparison() :
    m_timeToCheck(createValueField<Time::TimePeriod>(TIME_PERIOD_ATTRIBUTE_NAME, Time::TimePeriod::kMonth)),
    m_comparisonOperator(createValueField<Logic::ComparisonOperator>(COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_value(createValueField<size_t>(VALUE_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool TimeComparison::isConditionMet(
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
  bool TimeComparison::check(size_t currentTimePeriod) const
  {
    return Logic::isComparisonTrue(
      currentTimePeriod,
      getValue(),
      getComparisonOperator());
  }
}