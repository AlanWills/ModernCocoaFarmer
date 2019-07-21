#include "Lua/ScriptCommands/MCFScriptCommands.h"

#include "Lua/ScriptCommands/Managers/GameplayManagerScriptCommands.h"


namespace MCF
{
  namespace Lua
  {
    namespace MCFScriptCommands
    {
      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        GameplayManagerScriptCommands::initialize();
      }
    }
  }
}