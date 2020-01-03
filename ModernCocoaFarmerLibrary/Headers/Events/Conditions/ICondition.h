#pragma once

#include "Objects/ScriptableObject.h"

namespace MCF::Events::Conditions
{
  class ICondition : public CelesteEngine::ScriptableObject
  {
    public:
      virtual bool isConditionMet() const = 0;
  };
}