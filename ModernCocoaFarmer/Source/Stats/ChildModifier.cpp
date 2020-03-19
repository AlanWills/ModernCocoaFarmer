#include "Stats/ChildModifier.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF
{
  namespace Stats
  {
    REGISTER_SCRIPTABLE_OBJECT(ChildModifier);

    const std::string ChildModifier::APPLIES_TO_ALL_CHILDREN_FIELD_NAME = "applies_to_all_children";

    //------------------------------------------------------------------------------------------------
    ChildModifier::ChildModifier() :
      m_appliesToAllChildren(createValueField<bool>(APPLIES_TO_ALL_CHILDREN_FIELD_NAME, false))
    {
    }
  }
}