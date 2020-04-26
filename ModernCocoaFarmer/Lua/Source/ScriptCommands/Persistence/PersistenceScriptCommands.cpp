#include "ScriptCommands/Persistence/PersistenceScriptCommands.h"
#include "ScriptCommands/Persistence/DataStoreScriptCommands.h"
#include "ScriptCommands/Persistence/DataObjectHandleScriptCommands.h"


namespace MCF::Lua::Persistence::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    DataStoreScriptCommands::initialize(state);
    DataObjectHandleScriptCommands::initialize(state);
  }
}