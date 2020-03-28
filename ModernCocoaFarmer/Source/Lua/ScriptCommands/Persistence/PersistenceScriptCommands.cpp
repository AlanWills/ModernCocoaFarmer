#include "Lua/ScriptCommands/Persistence/PersistenceScriptCommands.h"
#include "Lua/ScriptCommands/Persistence/DataStoreScriptCommands.h"


namespace MCF::Lua::Persistence::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    DataStoreScriptCommands::initialize();
  }
}