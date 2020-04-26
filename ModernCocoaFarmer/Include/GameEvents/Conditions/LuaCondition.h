#pragma once

#include "MCFLibraryDllExport.h"
#include "GameEvents/Conditions/Condition.h"
#include "sol/sol.hpp"


namespace MCF::GameEvents::Conditions
{
  class LuaCondition : public Condition
  {
    DECLARE_SCRIPTABLE_OBJECT(LuaCondition, MCFLibraryDllExport);

    public:
      MCFLibraryDllExport void setIsConditionMetFunc(sol::protected_function isConditionMet) { m_isConditionMet = isConditionMet; }

      bool isConditionMet(
        Time::TimeManager& timeManager,
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager) const override;

    private:
      sol::protected_function m_isConditionMet;
  };
}