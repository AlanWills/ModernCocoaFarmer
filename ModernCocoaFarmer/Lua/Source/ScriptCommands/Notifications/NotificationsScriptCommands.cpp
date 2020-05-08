#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "ScriptCommands/Notifications/NotificationsScriptCommands.h"
#include "ScriptCommands/Notifications/NotificationScriptCommands.h"
#include "ScriptCommands/Notifications/NotificationManagerScriptCommands.h"


namespace MCF::Lua::Notifications::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    NotificationScriptCommands::initialize(state);
    NotificationManagerScriptCommands::initialize(state);
  }
}