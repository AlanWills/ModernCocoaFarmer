#include "Events/Effects/ModifyMoneyEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Money/MoneyManager.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ModifyMoneyEffect);

  //------------------------------------------------------------------------------------------------
  const char* const ModifyMoneyEffect::MODIFIER_PATH_ATTRIBUTE_NAME = "modifier_path";

  //------------------------------------------------------------------------------------------------
  ModifyMoneyEffect::ModifyMoneyEffect() :
    m_modifierPath(createReferenceField<std::string>(MODIFIER_PATH_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool ModifyMoneyEffect::trigger(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager&) const
  {
    auto modifier = ScriptableObject::load<Stats::Modifier>(getModifierPath());
    ASSERT(modifier != nullptr)
    
    if (modifier != nullptr)
    {
      moneyManager.applyMoneyModifier(*modifier);
    }
  }
}