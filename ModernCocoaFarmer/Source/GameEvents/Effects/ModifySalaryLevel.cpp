#include "GameEvents/Effects/ModifySalaryLevel.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Money/MoneyManager.h"


namespace MCF::GameEvents::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ModifySalaryLevel);

  //------------------------------------------------------------------------------------------------
  const char* const ModifySalaryLevel::MODIFIER_ATTRIBUTE_NAME = "modifier";

  //------------------------------------------------------------------------------------------------
  ModifySalaryLevel::ModifySalaryLevel() :
    m_modifier(createValueField<int>(MODIFIER_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ModifySalaryLevel::trigger(
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