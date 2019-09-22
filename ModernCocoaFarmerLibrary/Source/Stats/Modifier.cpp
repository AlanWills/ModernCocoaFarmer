#include "Stats/Modifier.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF
{
  namespace Stats
  {
    REGISTER_SCRIPTABLE_OBJECT(Modifier);

    //------------------------------------------------------------------------------------------------
    const std::string Modifier::AMOUNT_FIELD_NAME = "amount";
    const std::string Modifier::CHANGE_TYPE_FIELD_NAME = "change_type";
    const std::string Modifier::OCCURRENCE_FIELD_NAME = "occurrence";
    const std::string Modifier::MONTHLY_FREQUENCY_FIELD_NAME = "monthly_frequency";

    //------------------------------------------------------------------------------------------------
    Modifier::Modifier() :
      m_amount(createValueField<int>(AMOUNT_FIELD_NAME)),
      m_changeType(createValueField<ChangeType>(CHANGE_TYPE_FIELD_NAME)),
      m_occurrence(createValueField<Occurrence>(OCCURRENCE_FIELD_NAME)),
      m_monthlyFrequency(createValueField<float>(MONTHLY_FREQUENCY_FIELD_NAME))
    {
    }
  }
}