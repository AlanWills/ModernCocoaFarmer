#pragma once

#include "MCFLibraryDllExport.h"
#include "GameEvents/Effects/Effect.h"
#include "sol/sol.hpp"


namespace MCF::GameEvents::Effects
{
  class LuaEffect : public Effect
  {
    DECLARE_SCRIPTABLE_OBJECT(LuaEffect, MCFLibraryDllExport);

  public:
    MCFLibraryDllExport void setTriggerFunc(sol::protected_function trigger) { m_trigger = trigger; }

    void trigger(
      Money::MoneyManager& moneyManager,
      Family::FamilyManager& familyManager,
      Locations::LocationsManager& locationManager,
      Notifications::NotificationManager& notificationManager) const override;

  private:
    sol::protected_function m_trigger;
  };
}