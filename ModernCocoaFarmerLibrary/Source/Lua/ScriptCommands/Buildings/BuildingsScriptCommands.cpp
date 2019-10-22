#include "Lua/ScriptCommands/Buildings/BuildingsScriptCommands.h"
#include "Lua/ScriptCommands/Buildings/BuildingInformationScriptCommands.h"


namespace MCF
{
  namespace Lua
  {
    namespace Buildings
    {
      namespace ScriptCommands
      {
        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          BuildingInformationScriptCommands::initialize();
        }
      }
    }
  }
}