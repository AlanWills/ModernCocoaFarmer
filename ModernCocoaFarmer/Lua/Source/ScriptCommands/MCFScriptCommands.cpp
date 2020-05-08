#include "ScriptCommands/MCFScriptCommands.h"
#include "ScriptCommands/Animation/ScriptCommands.h"
#include "ScriptCommands/Locations/LocationsScriptCommands.h"
#include "ScriptCommands/Notifications/NotificationsScriptCommands.h"
#include "ScriptCommands/Family/FamilyScriptCommands.h"
#include "ScriptCommands/Money/MoneyScriptCommands.h"
#include "ScriptCommands/Stats/StatsScriptCommands.h"
#include "ScriptCommands/Persistence/PersistenceScriptCommands.h"
#include "ScriptCommands/Time/TimeScriptCommands.h"


namespace MCF::Lua::MCFScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Animation::ScriptCommands::initialize(state);
    Locations::ScriptCommands::initialize(state);
    Notifications::ScriptCommands::initialize(state);
    Family::ScriptCommands::initialize(state);
    Money::ScriptCommands::initialize(state);
    Stats::ScriptCommands::initialize(state);
    Persistence::ScriptCommands::initialize(state);
    Time::ScriptCommands::initialize(state);
  }
}