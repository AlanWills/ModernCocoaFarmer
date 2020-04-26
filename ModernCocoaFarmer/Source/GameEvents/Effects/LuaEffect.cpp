#include "GameEvents/Effects/LuaEffect.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"

#include "Money/MoneyManager.h"
#include "Family/FamilyManager.h"
#include "Locations/LocationsManager.h"
#include "Notifications/NotificationManager.h"


namespace MCF::GameEvents::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(LuaEffect);

  //------------------------------------------------------------------------------------------------
  LuaEffect::LuaEffect() = default;

  //------------------------------------------------------------------------------------------------
  void LuaEffect::trigger(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager& locationManager,
    Notifications::NotificationManager& notificationManager) const
  {
    if (m_trigger.valid())
    {
      sol::protected_function_result result = m_trigger.call(moneyManager, familyManager, locationManager, notificationManager);

      if (!result.valid())
      {
        sol::error e = result;
        LOG_ERROR(e.what());
        ASSERT_FAIL();
      }
    }
  }
}