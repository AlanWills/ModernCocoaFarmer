#include "Lua/ScriptCommands/MCFScriptCommands.h"

#include "Lua/ScriptCommands/Managers/GameplayManagerScriptCommands.h"
#include "Lua/ScriptCommands/UI/UIScriptCommands.h"


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
        UIScriptCommands::initialize();
      }
    }
  }
}