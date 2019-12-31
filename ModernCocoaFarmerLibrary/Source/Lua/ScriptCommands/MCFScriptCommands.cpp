#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingsScriptCommands.h"
#include "Lua/ScriptCommands/Events/EventScriptCommands.h"
#include "Lua/ScriptCommands/Family/FamilyScriptCommands.h"
#include "Lua/ScriptCommands/Money/MoneyScriptCommands.h"
#include "Lua/ScriptCommands/Stats/StatsScriptCommands.h"
#include "Lua/ScriptCommands/Persistence/PersistenceScriptCommands.h"
#include "Lua/ScriptCommands/Time/TimeScriptCommands.h"


namespace MCF
{
  namespace Lua
  {
    namespace MCFScriptCommands
    {
      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        Buildings::ScriptCommands::initialize();
        Events::ScriptCommands::initialize();
        Family::ScriptCommands::initialize();
        Money::ScriptCommands::initialize();
        Stats::ScriptCommands::initialize();
        Persistence::ScriptCommands::initialize();
        Time::ScriptCommands::initialize();
      }
    }
  }
}