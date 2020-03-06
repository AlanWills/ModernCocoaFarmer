#include "Notifications/NotificationManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF::Notifications
{
  //------------------------------------------------------------------------------------------------
  REGISTER_UNMANAGED_COMPONENTABLE_OBJECT(NotificationManager);

  //------------------------------------------------------------------------------------------------
  NotificationManager::NotificationManager() :
    m_onNotificationSentEvent()
  {
  }

  //------------------------------------------------------------------------------------------------
  void NotificationManager::sendNotification(const Notification& notification) const
  {
    m_onNotificationSentEvent.invoke(notification);
  }
}