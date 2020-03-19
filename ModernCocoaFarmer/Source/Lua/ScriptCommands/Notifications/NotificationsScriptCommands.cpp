#include "Lua/ScriptCommands/GameEvents/GameEventManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Lua/ScriptCommands/Notifications/NotificationsScriptCommands.h"
#include "Lua/ScriptCommands/Notifications/NotificationScriptCommands.h"
#include "Lua/ScriptCommands/Notifications/NotificationManagerScriptCommands.h"


namespace MCF::Lua::Notifications::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    NotificationScriptCommands::initialize();
    NotificationManagerScriptCommands::initialize();
  }
}