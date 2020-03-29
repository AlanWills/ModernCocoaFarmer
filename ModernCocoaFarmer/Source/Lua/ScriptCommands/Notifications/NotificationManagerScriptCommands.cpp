#include "Lua/ScriptCommands/Notifications/NotificationManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

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
  void initialize()
  {
    Celeste::Lua::registerScriptableObjectUserType<NotificationManager>(
      NotificationManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "subscribeOnNotificationSentCallback", &Internals::subscribeOnNotificationSentCallback);
  }
}