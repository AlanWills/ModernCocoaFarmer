#pragma once

#include "Objects/ScriptableObject.h"


namespace MCF::Time
{
  class TimeManager;
}

namespace MCF::Money
{
  class MoneyManager;
}

namespace MCF::Family
{
  class FamilyManager;
}

namespace MCF::Events::Conditions
{
  class Condition : public Celeste::ScriptableObject
  {
    public:
      virtual bool isConditionMet(
        Time::TimeManager& timeManager, 
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const = 0;
  };
}