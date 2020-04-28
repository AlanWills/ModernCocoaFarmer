#include "GameEvents/Effects/SendNotification.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Notifications/NotificationManager.h"
#include "Notifications/Notification.h"

using namespace MCF::Notifications;


namespace MCF::GameEvents::Effects
{
  REGISTER_SCRIPTABLE_OBJECT(SendNotification);

  //------------------------------------------------------------------------------------------------
  SendNotification::SendNotification() :
    m_notification(createScriptableObject<Notification>("notification"))
  {
  }

  //------------------------------------------------------------------------------------------------
  void SendNotification::trigger(
    Money::MoneyManager&,
    Family::FamilyManager&,
    Locations::LocationsManager&,
    NotificationManager& notificationManager) const
  {
    const Notification& notification = getNotification();
    
    std::unique_ptr<Notification> newNotification = ScriptableObject::create<Notification>(notification.getName());
    newNotification->setDescription(notification.getDescription());
    newNotification->setIcon(notification.getIcon());

    notificationManager.sendNotification(std::move(newNotification));
  }
}