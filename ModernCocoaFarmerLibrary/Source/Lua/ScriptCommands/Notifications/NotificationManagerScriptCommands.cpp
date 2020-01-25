#include "Lua/ScriptCommands/Notifications/NotificationManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Notifications/NotificationManager.h"
#include "Notifications/Notification.h"

using namespace MCF::Notifications;


namespace MCF::Lua::Notifications::NotificationManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void subscribeOnGameEventTriggeredCallback(
      NotificationManager& notificationManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<NotificationManager::NotificationSentEvent, const Notification&>(
        notificationManager.getNotificationSentEvent(),
        callback,
        extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CelesteEngine::Lua::registerScriptableObjectUserType<NotificationManager>(
      NotificationManager::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "subscribeOnNotificationSentCallback", &Internals::subscribeOnGameEventTriggeredCallback);
  }
}