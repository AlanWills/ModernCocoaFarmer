#include "ScriptCommands/Notifications/NotificationScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Notifications/Notification.h"

#include "Resources/ResourceManager.h"
#include "Resources/ResourceUtils.h"

using namespace Celeste::Resources;
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
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void setIcon(Notification& notification, const std::string& texturePath)
    {
      notification.setIcon(getResourceManager().load<Texture2D>(texturePath));
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerScriptableObjectUserType<Notification>(
      state,
      Notification::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "getDescription", &Notification::getDescription,
      "setDescription", &Notification::setDescription,
      "getIcon", &Notification::getIcon,
      "setIcon", &Internals::setIcon);
  }
}