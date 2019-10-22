#include "Lua/ScriptCommands/Persistence/PersistenceScriptCommands.h"
#include "Lua/ScriptCommands/Persistence/DataStoreScriptCommands.h"


namespace MCF
{
  namespace Lua
  {
    namespace Persistence
    {
      namespace ScriptCommands
      {
        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          DataStoreScriptCommands::initialize();
        }
      }
    }
  }
}