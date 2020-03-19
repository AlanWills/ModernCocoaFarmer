#include "GameEvents/Conditions/RandomNumberComparison.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Time/TimeManager.h"
#include "Deserialization/Logic/LogicDeserializers.h"
#include "Maths/RandomGenerator.h"


namespace MCF::GameEvents::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(RandomNumberComparison);

  //------------------------------------------------------------------------------------------------
  const char* const RandomNumberComparison::COMPARISON_OPERATOR_ATTRIBUTE_NAME = "comparison_operator";
  const char* const RandomNumberComparison::VALUE_ATTRIBUTE_NAME = "value";

  //------------------------------------------------------------------------------------------------
  RandomNumberComparison::RandomNumberComparison() :
    m_comparisonOperator(createValueField<Logic::ComparisonOperator>(COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_value(createValueField<float>(VALUE_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool RandomNumberComparison::isConditionMet(
    Time::TimeManager&,
    Money::MoneyManager&,
    Family::FamilyManager&) const
  {
    return Logic::isComparisonTrue(
      Celeste::Random::generate(),
      getValue(),
      getComparisonOperator());
  }
}