#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"


namespace MCF::Money
{
  class MoneyManager;
}

namespace MCF::Family
{
  class FamilyManager;
}

namespace MCF::Locations
{
  class LocationsManager;
}

namespace MCF::Notifications
{
  class NotificationManager;
}

namespace MCF::Events::Effects
{
  class Effect : public Celeste::ScriptableObject
  {
    public:
      virtual ~Effect() = default;

      virtual void trigger(
        Money::MoneyManager& moneyManager, 
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationManager,
        Notifications::NotificationManager& notificationManager) const = 0;
  };
}