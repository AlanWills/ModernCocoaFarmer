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

namespace MCF::Events::Effects
{
  class Effect : public CelesteEngine::ScriptableObject
  {
    public:
      virtual bool trigger(
        Money::MoneyManager& moneyManager, 
        Family::FamilyManager& familyManager) const = 0;
  };
}