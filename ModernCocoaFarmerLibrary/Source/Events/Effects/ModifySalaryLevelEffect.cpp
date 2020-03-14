#include "Events/Effects/ModifySalaryLevelEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Money/MoneyManager.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ModifySalaryLevelEffect);

  //------------------------------------------------------------------------------------------------
  const char* const ModifySalaryLevelEffect::MODIFIER_ATTRIBUTE_NAME = "modifier";

  //------------------------------------------------------------------------------------------------
  ModifySalaryLevelEffect::ModifySalaryLevelEffect() :
    m_modifier(createValueField<int>(MODIFIER_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ModifySalaryLevelEffect::trigger(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager&,
    Locations::LocationsManager&,
    Notifications::NotificationManager&) const
  {
    if (getModifier() < 0)
    {
      for (int i = 0, n = -getModifier(); i < n; ++i)
      {
        moneyManager.decrementSalaryLevel();
      }
    }
    else
    {
      moneyManager.setSalaryLevel(moneyManager.getSalaryLevel() + static_cast<unsigned int>(getModifier()));
    }
  }
}