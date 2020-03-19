#include "GameEvents/Effects/ModifyMoney.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Money/MoneyManager.h"
#include "Stats/Modifier.h"


namespace MCF::GameEvents::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ModifyMoney);

  //------------------------------------------------------------------------------------------------
  const char* const ModifyMoney::MODIFIER_PATH_ATTRIBUTE_NAME = "modifier_path";

  //------------------------------------------------------------------------------------------------
  ModifyMoney::ModifyMoney() :
    m_modifierPath(createReferenceField<std::string>(MODIFIER_PATH_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ModifyMoney::trigger(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager&,
    Locations::LocationsManager&,
    Notifications::NotificationManager&) const
  {
    auto modifier = ScriptableObject::load<Stats::Modifier>(getModifierPath());
    ASSERT(modifier != nullptr);
    
    if (modifier != nullptr)
    {
      moneyManager.applyMoneyModifier(*modifier);
    }
  }
}