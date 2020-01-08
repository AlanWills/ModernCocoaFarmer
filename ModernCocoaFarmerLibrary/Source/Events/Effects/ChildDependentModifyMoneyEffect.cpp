#include "Events/Effects/ChildDependentModifyMoneyEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Money/MoneyManager.h"
#include "Family/FamilyManager.h"
#include "Stats/Modifier.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(ChildDependentModifyMoneyEffect);

  //------------------------------------------------------------------------------------------------
  ChildDependentModifyMoneyEffect::ChildDependentModifyMoneyEffect() :
    Inherited()
  {
  }

  //------------------------------------------------------------------------------------------------
  void ChildDependentModifyMoneyEffect::trigger(Money::MoneyManager& moneyManager, Family::FamilyManager& familyManager) const
  {
    auto modifier = ScriptableObject::load<Stats::Modifier>(getModifierPath());
    ASSERT(modifier != nullptr);

    if (modifier != nullptr)
    {
      modifier->setAmount(modifier->getAmount() * static_cast<int>(familyManager.getChildCount()));
      moneyManager.applyMoneyModifier(*modifier);
    }
  }
}