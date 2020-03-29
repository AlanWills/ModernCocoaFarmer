#include "Lua/ScriptCommands/Notifications/NotificationScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Notifications/Notification.h"

using namespace MCF::Notifications;


namespace sol
{
  template <>
  struct is_to_stringable<Notification> : std::false_type {};

  template <>
  struct is_to_stringable<Celeste::Resources::Texture2D> : std::false_type {};
}

namespace MCF::Lua::Notifications::NotificationScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    Celeste::Lua::registerScriptableObjectUserType<Notification>(
      Notification::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "getDescription", &Notification::getDescription,
      "getIcon", &Notification::getIcon);
  }
}