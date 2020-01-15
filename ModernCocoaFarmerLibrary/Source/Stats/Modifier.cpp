#include "Stats/Modifier.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF
{
  namespace Stats
  {
    REGISTER_SCRIPTABLE_OBJECT(Modifier);

    //------------------------------------------------------------------------------------------------
    const char* const Modifier::AMOUNT_FIELD_NAME = "amount";
    const char* const Modifier::CHANGE_TYPE_FIELD_NAME = "change_type";
    const char* const Modifier::OCCURRENCE_FIELD_NAME = "occurrence";
    const char* const Modifier::PERIOD_IN_MONTHS_FIELD_NAME = "period_in_months";

    //------------------------------------------------------------------------------------------------
    Modifier::Modifier() :
      m_amount(createValueField<float>(AMOUNT_FIELD_NAME)),
      m_changeType(createValueField<ChangeType>(CHANGE_TYPE_FIELD_NAME)),
      m_occurrence(createValueField<Occurrence>(OCCURRENCE_FIELD_NAME)),
      m_periodInMonths(createValueField<float>(PERIOD_IN_MONTHS_FIELD_NAME))
    {
    }
  }
}