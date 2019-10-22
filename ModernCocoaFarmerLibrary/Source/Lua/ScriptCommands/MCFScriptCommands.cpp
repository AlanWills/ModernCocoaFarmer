#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingsScriptCommands.h"
#include "Lua/ScriptCommands/Stats/StatsScriptCommands.h"
#include "Lua/ScriptCommands/Persistence/PersistenceScriptCommands.h"


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
        Stats::ScriptCommands::initialize();
        Persistence::ScriptCommands::initialize();
      }
    }
  }
}