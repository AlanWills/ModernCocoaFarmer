#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingInformationScriptCommands.h"
#include "Lua/ScriptCommands/Stats/ModifierScriptCommands.h"
#include "Lua/ScriptCommands/Stats/ChildModifierScriptCommands.h"


namespace MCF
{
  namespace Lua
  {
    namespace MCFScriptCommands
    {
      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        BuildingInformationScriptCommands::initialize();
        Stats::ModifierScriptCommands::initialize();
        Stats::ChildModifierScriptCommands::initialize();
      }
    }
  }
}