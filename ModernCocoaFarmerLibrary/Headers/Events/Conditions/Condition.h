#pragma once

#include "Objects/ScriptableObject.h"


namespace MCF::Time
{
  class TimeManager;
}

namespace MCF::Events::Conditions
{
  class Condition : public CelesteEngine::ScriptableObject
  {
    public:
      virtual bool isConditionMet(Time::TimeManager& timeManager) const = 0;
  };
}