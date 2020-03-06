#include "Events/Effects/TriggerDailyFamilyModifications.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/FamilyManager.h"


namespace MCF::Events::Effects
{
  REGISTER_UNMANAGED_COMPONENTABLE_OBJECT(TriggerDailyFamilyModifications);

  //------------------------------------------------------------------------------------------------
  TriggerDailyFamilyModifications::TriggerDailyFamilyModifications()
  {
  }

  //------------------------------------------------------------------------------------------------
  void TriggerDailyFamilyModifications::trigger(
    Money::MoneyManager&,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager&,
    Notifications::NotificationManager&) const
  {
    familyManager.applyDailyModifiers();
  }
}