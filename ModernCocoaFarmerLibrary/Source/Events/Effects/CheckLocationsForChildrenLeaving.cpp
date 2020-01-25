#include "Events/Effects/CheckLocationsForChildrenLeaving.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Locations/LocationsManager.h"


namespace MCF::Events::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(CheckLocationsForChildrenLeaving);

  //------------------------------------------------------------------------------------------------
  CheckLocationsForChildrenLeaving::CheckLocationsForChildrenLeaving()
  {
  }

  //------------------------------------------------------------------------------------------------
  void CheckLocationsForChildrenLeaving::trigger(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager& locationsManager,
    Notifications::NotificationManager& notificationsManager) const
  {
    locationsManager.checkLocationsForChildrenLeaving(moneyManager, familyManager, notificationsManager);
  }
}