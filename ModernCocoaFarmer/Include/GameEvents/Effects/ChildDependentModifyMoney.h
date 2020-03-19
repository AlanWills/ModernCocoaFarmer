#pragma once

#include "GameEvents\Effects\ModifyMoney.h"


namespace MCF::GameEvents::Effects
{
  class ChildDependentModifyMoney : public ModifyMoney
  {
    DECLARE_SCRIPTABLE_OBJECT(ChildDependentModifyMoney, MCFLibraryDllExport);

    public:
      void trigger(
        Money::MoneyManager& moneyManager, 
        Family::FamilyManager& familyManager,
        Locations::LocationsManager&,
        Notifications::NotificationManager&) const override;

    private:
      using Inherited = ModifyMoney;
  };
}