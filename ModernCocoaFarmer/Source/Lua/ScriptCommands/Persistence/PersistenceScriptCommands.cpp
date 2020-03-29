#include "Lua/ScriptCommands/Persistence/PersistenceScriptCommands.h"
#include "Lua/ScriptCommands/Persistence/DataStoreScriptCommands.h"
#include "Lua/ScriptCommands/Persistence/DataObjectHandleScriptCommands.h"


namespace MCF::Lua::Persistence::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    DataStoreScriptCommands::initialize();
    DataObjectHandleScriptCommands::initialize();
  }
}