#include "Lua/ScriptCommands/Stats/StatsScriptCommands.h"
#include "Lua/ScriptCommands/Stats/ModifierScriptCommands.h"
#include "Lua/ScriptCommands/Stats/ChildModifierScriptCommands.h"


namespace MCF
{
  namespace Lua
  {
    namespace Stats
    {
      namespace ScriptCommands
      {
        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          ModifierScriptCommands::initialize();
          ChildModifierScriptCommands::initialize();
        }
      }
    }
  }
}