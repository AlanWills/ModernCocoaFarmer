#include "Events/Effects/TriggerDailyLocationModifications.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Locations/LocationsManager.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(TriggerDailyLocationModifications);

  //------------------------------------------------------------------------------------------------
  TriggerDailyLocationModifications::TriggerDailyLocationModifications()
  {
  }

  //------------------------------------------------------------------------------------------------
  void TriggerDailyLocationModifications::trigger(
    Money::MoneyManager&,
    Family::FamilyManager&,
    Locations::LocationsManager& locationsManager,
    Notifications::NotificationManager&) const
  {
    locationsManager.applyDailyModifiers();
  }
}