#pragma once

#include "GameEvents/Effects/Effect.h"


namespace MCF::GameEvents::Effects
{
  class CheckLocationsForChildrenArriving : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(CheckLocationsForChildrenArriving, MCFLibraryDllExport);

    public:
      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationManager,
        Notifications::NotificationManager& notificationManager) const override;
  };
}