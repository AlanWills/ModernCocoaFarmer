#include "Notifications/NotificationManager.h"
#include "Notifications/Notification.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"

using namespace Celeste::XML;


namespace MCF::Notifications
{
  //------------------------------------------------------------------------------------------------
  REGISTER_SCRIPTABLE_OBJECT(NotificationManager);

  //------------------------------------------------------------------------------------------------
  const char* const NotificationManager::NOTIFICATION_ELEMENT_NAME = "Notification";

  //------------------------------------------------------------------------------------------------
  NotificationManager::NotificationManager() :
    m_notifications(),
    m_onNotificationSentEvent()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool NotificationManager::doDeserialize(const tinyxml2::XMLElement* element)
  {
    for (const tinyxml2::XMLElement* notification : children(element, NOTIFICATION_ELEMENT_NAME))
    {
      m_notifications.push_back(deserializeScriptableObject<const Notification>(notification));
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<const Notification> NotificationManager::getNotification(size_t index) const
  {
    return index < getNotificationCount() ? &m_notifications[index].get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void NotificationManager::sendNotification(std::unique_ptr<Notification>&& notification)
  {
    m_notifications.push_back(addScriptableObject<Notification>(std::move(notification)));
    m_onNotificationSentEvent.invoke(m_notifications.back());
  }

  //------------------------------------------------------------------------------------------------
  void NotificationManager::removeNotification(const Notification& notification)
  {
    for (size_t i = 0; i < m_notifications.size(); ++i)
    {
      if (&m_notifications[i].get() == &notification)
      {
        m_notifications.erase(m_notifications.begin() + i);
        return;
      }
    }
  }
}