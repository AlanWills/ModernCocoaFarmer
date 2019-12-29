#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingsScriptCommands.h"
#include "Lua/ScriptCommands/Family/FamilyScriptCommands.h"
#include "Lua/ScriptCommands/Stats/StatsScriptCommands.h"
#include "Lua/ScriptCommands/Persistence/PersistenceScriptCommands.h"
#include "Lua/ScriptCommands/Time/TimeNotifierScriptCommands.h"


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
        Family::ScriptCommands::initialize();
        Stats::ScriptCommands::initialize();
        Persistence::ScriptCommands::initialize();
        Time::TimeNotifierScriptCommands::initialize();
      }
    }
  }
}