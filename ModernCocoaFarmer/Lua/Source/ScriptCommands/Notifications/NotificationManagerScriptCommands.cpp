#include "ScriptCommands/Notifications/NotificationManagerScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Notifications/NotificationManager.h"
#include "Notifications/Notification.h"

using namespace MCF::Notifications;


namespace sol
{
  template <>
  struct is_to_stringable<NotificationManager> : std::false_type {};
}

namespace MCF::Lua::Notifications::NotificationManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void sendNotification(NotificationManager& notificationManager, std::unique_ptr<Notification>& notification)
    {
      notificationManager.sendNotification(std::move(notification));
    }

    //------------------------------------------------------------------------------------------------
    void removeNotification_Notification(NotificationManager& notificationManager, const Notification& notification)
    {
      notificationManager.removeNotification(notification);
    }

    //------------------------------------------------------------------------------------------------
    void removeNotification_Index(NotificationManager& notificationManager, size_t notificationIndex)
    {
      notificationManager.removeNotification(notificationIndex);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnNotificationSentCallback(
      NotificationManager& notificationManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<NotificationManager::NotificationSentEvent, const Notification&>(
        notificationManager.getNotificationSentEvent(),
        callback,
        extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerScriptableObjectUserType<NotificationManager>(
      state,
      NotificationManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "getNotificationCount", &NotificationManager::getNotificationCount,
      "getNotification", &NotificationManager::getNotification,
      "sendNotification", &Internals::sendNotification,
      "removeNotification", sol::overload(&Internals::removeNotification_Notification, &Internals::removeNotification_Index),
      "subscribeOnNotificationSentCallback", &Internals::subscribeOnNotificationSentCallback);
  }
}