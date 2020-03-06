#pragma once

#include "Events/Effects/Effect.h"


namespace MCF::Events::Effects
{
  class CheckLocationsForChildrenLeaving : public Effect
  {
    DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(CheckLocationsForChildrenLeaving, MCFLibraryDllExport);

  public:
    void trigger(
      Money::MoneyManager& moneyManager,
      Family::FamilyManager& familyManager,
      Locations::LocationsManager& locationManager,
      Notifications::NotificationManager& notificationManager) const override;
  };
}