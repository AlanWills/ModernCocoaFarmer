#include "Events/Effects/TriggerDailyFamilyModifications.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/FamilyManager.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(TriggerDailyFamilyModifications);

  //------------------------------------------------------------------------------------------------
  TriggerDailyFamilyModifications::TriggerDailyFamilyModifications()
  {
  }

  //------------------------------------------------------------------------------------------------
  void TriggerDailyFamilyModifications::trigger(
    Money::MoneyManager&,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager&) const
  {
    familyManager.applyDailyModifiers();
  }
}