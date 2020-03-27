#include "Stats/Modifier.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF::Stats
{
  REGISTER_SCRIPTABLE_OBJECT(Modifier);

  //------------------------------------------------------------------------------------------------
  const char* const Modifier::AMOUNT_FIELD_NAME = "amount";
  const char* const Modifier::CHANGE_TYPE_FIELD_NAME = "change_type";

  //------------------------------------------------------------------------------------------------
  Modifier::Modifier() :
    m_amount(createValueField<float>(AMOUNT_FIELD_NAME)),
    m_changeType(createValueField<ChangeType>(CHANGE_TYPE_FIELD_NAME))
  {
  }
}