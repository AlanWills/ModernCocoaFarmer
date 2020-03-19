#include "GameEvents/Effects/PaySalary.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Money/MoneyManager.h"
#include "Stats/Modifier.h"


namespace MCF::GameEvents::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(PaySalary);

  //------------------------------------------------------------------------------------------------
  PaySalary::PaySalary() = default;

  //------------------------------------------------------------------------------------------------
  void PaySalary::trigger(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager&,
    Locations::LocationsManager&,
    Notifications::NotificationManager&) const
  {
    auto modifier = ScriptableObject::load<Stats::Modifier>(getModifierPath());
    ASSERT(modifier != nullptr);

    if (modifier != nullptr)
    {
      modifier->setAmount(modifier->getAmount() * moneyManager.getSalaryLevel());
      moneyManager.applyMoneyModifier(*modifier);
    }
  }
}