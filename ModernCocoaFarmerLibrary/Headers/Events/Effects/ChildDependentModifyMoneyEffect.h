#pragma once

#include "Events\Effects\ModifyMoneyEffect.h"


namespace MCF::Events::Effects
{
  class ChildDependentModifyMoneyEffect : public ModifyMoneyEffect
  {
    DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(ChildDependentModifyMoneyEffect, MCFLibraryDllExport);

    public:
      void trigger(
        Money::MoneyManager& moneyManager, 
        Family::FamilyManager& familyManager,
        Locations::LocationsManager&,
        Notifications::NotificationManager&) const override;

    private:
      using Inherited = ModifyMoneyEffect;
  };
}