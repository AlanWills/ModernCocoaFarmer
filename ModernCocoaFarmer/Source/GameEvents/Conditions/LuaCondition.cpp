#include "GameEvents/Conditions/LuaCondition.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"

#include "Time/TimeManager.h"
#include "Money/MoneyManager.h"
#include "Family/FamilyManager.h"


namespace MCF::GameEvents::Conditions
{
  REGISTER_SCRIPTABLE_OBJECT(LuaCondition);

  //------------------------------------------------------------------------------------------------
  LuaCondition::LuaCondition() = default;

  //------------------------------------------------------------------------------------------------
  bool LuaCondition::isConditionMet(
    Time::TimeManager& timeManager,
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager) const
  {
    if (m_isConditionMet.valid())
    {
      sol::protected_function_result result = m_isConditionMet.call(timeManager, moneyManager, familyManager);
      
      if (!result.valid())
      {
        sol::error e = result;
        LOG_ERROR(e.what());
        ASSERT_FAIL();

        return false;
      }

      return result.get<bool>();
    }

    return true;
  }
}