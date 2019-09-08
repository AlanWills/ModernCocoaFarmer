#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingInformationScriptCommands.h"


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
      }
    }
  }
}