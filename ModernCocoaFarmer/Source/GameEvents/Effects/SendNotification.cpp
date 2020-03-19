#include "GameEvents/Effects/SendNotification.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Notifications/NotificationManager.h"
#include "Notifications/Notification.h"


namespace MCF::GameEvents::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(SendNotification);

  //------------------------------------------------------------------------------------------------
  SendNotification::SendNotification() :
    m_notification(createScriptableObject<Notifications::Notification>("notification"))
  {
  }

  //------------------------------------------------------------------------------------------------
  void SendNotification::trigger(
    Money::MoneyManager&,
    Family::FamilyManager&,
    Locations::LocationsManager&,
    Notifications::NotificationManager& notificationManager) const
  {
    notificationManager.sendNotification(getNotification());
  }
}