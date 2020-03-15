#pragma once

#include "Events/Effects/ModifyMoney.h"


namespace MCF::Events::Effects
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