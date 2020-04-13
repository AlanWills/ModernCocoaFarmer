#pragma once

#include "GameEvents/Effects/Effect.h"


namespace MCF::GameEvents::Effects
{
  class TriggerDailyFamilyModifications : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(TriggerDailyFamilyModifications, MCFLibraryDllExport);

  public:
    void trigger(
      Money::MoneyManager& moneyManager,
      Family::FamilyManager& familyManager,
      Locations::LocationsManager& locationManager,
      Notifications::NotificationManager& notificationManager) const override;
  };
}