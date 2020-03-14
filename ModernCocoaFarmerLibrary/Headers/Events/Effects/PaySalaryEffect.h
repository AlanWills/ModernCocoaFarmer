#pragma once

#include "Events/Effects/ModifyMoneyEffect.h"


namespace MCF::Events::Effects
{
  class PaySalaryEffect : public ModifyMoneyEffect
  {
    DECLARE_SCRIPTABLE_OBJECT(PaySalaryEffect, MCFLibraryDllExport);

    public:
      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationManager,
          Notifications::NotificationManager& notificationManager) const override;
  };
}