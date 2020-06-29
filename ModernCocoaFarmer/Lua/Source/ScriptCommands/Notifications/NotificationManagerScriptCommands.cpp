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

    //------------------------------------------------------------------------------------------------
    void unsubscribeAll(NotificationManager& notificationManager)
    {
      notificationManager.getNotificationSentEvent().unsubscribeAll();
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
      "removeNotification", &NotificationManager::removeNotification,
      "subscribeOnNotificationSentCallback", &Internals::subscribeOnNotificationSentCallback,
      "unsubscribeAll", &Internals::unsubscribeAll);
  }
}