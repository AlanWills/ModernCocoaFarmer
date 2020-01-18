#pragma once

#include "Events/Effects/Effect.h"


namespace MCF::Events::Effects
{
  class TriggerDailyLocationModifications : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(TriggerDailyLocationModifications, MCFLibraryDllExport);

    public:
      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationManager) const override;
  };
}