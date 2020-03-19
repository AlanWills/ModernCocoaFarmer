#pragma once

#include "GameEvents/Effects/ModifyMoney.h"


namespace MCF::GameEvents::Effects
{
  class PaySalary : public ModifyMoney
  {
    DECLARE_SCRIPTABLE_OBJECT(PaySalary, MCFLibraryDllExport);

    public:
      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationManager,
          Notifications::NotificationManager& notificationManager) const override;
  };
}