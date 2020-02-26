#include "Events/Conditions/CheckDataStoreBoolValueCondition.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Deserialization/Logic/LogicDeserializers.h"
#include "Persistence/DataStore.h"
#include "Resources/ResourceUtils.h"
#include "Resources/ResourceManager.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace MCF::Events::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(CheckDataStoreBoolValueCondition);

  //------------------------------------------------------------------------------------------------
  const char* const CheckDataStoreBoolValueCondition::DATA_STORE_PATH_ATTRIBUTE_NAME = "data_store_path";
  const char* const CheckDataStoreBoolValueCondition::VALUE_NAME_ATTRIBUTE_NAME = "value_name";
  const char* const CheckDataStoreBoolValueCondition::COMPARISON_OPERATOR_ATTRIBUTE_NAME = "comparison_operator";
  const char* const CheckDataStoreBoolValueCondition::EXPECTED_VALUE_ATTRIBUTE_NAME = "expected_value";
  const char* const CheckDataStoreBoolValueCondition::DEFAULT_VALUE_ATTRIBUTE_NAME = "default_value";

  //------------------------------------------------------------------------------------------------
  CheckDataStoreBoolValueCondition::CheckDataStoreBoolValueCondition() :
    m_dataStorePath(createReferenceField<std::string>(DATA_STORE_PATH_ATTRIBUTE_NAME)),
    m_valueName(createReferenceField<std::string>(VALUE_NAME_ATTRIBUTE_NAME)),
    m_comparisonOperator(createValueField<Logic::ComparisonOperator>(COMPARISON_OPERATOR_ATTRIBUTE_NAME, Logic::ComparisonOperator::kEqual)),
    m_expectedValue(createValueField<bool>(EXPECTED_VALUE_ATTRIBUTE_NAME)),
    m_defaultValue(createValueField<bool>(DEFAULT_VALUE_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool CheckDataStoreBoolValueCondition::isConditionMet(
    Time::TimeManager&,
    Money::MoneyManager&,
    Family::FamilyManager&) const
  {
    observer_ptr<Data> data = getResourceManager().load<Data>(getDataStorePath());
    if (data == nullptr)
    {
      ASSERT_FAIL();
      return getExpectedValue() == getDefaultValue();
    }

    Persistence::DataStore dataStore = Persistence::DataStore::deserialize(*data->getDocumentRoot());

    return Logic::isComparisonTrue(
      dataStore.get<bool>(getValueName(), getDefaultValue()),
      getExpectedValue(),
      getComparisonOperator());
  }
}