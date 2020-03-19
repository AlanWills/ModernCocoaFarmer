#include "GameEvents/Effects/CheckLocationsForChildrenArriving.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Locations/LocationsManager.h"


namespace MCF::GameEvents::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(CheckLocationsForChildrenArriving);

  //------------------------------------------------------------------------------------------------
  CheckLocationsForChildrenArriving::CheckLocationsForChildrenArriving() = default;

  //------------------------------------------------------------------------------------------------
  void CheckLocationsForChildrenArriving::trigger(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager& locationsManager,
    Notifications::NotificationManager& notificationsManager) const
  {
    locationsManager.checkLocationsForChildrenArriving(moneyManager, familyManager, notificationsManager);
  }
}