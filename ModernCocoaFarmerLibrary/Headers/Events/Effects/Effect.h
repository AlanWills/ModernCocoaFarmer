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

namespace MCF::Events::Effects
{
  class Effect : public CelesteEngine::ScriptableObject
  {
    public:
      virtual void trigger(
        Money::MoneyManager& moneyManager, 
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationManager) const = 0;
  };
}