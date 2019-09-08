#include "Lua/ScriptCommands/Buildings/BuildingInformationScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Buildings/BuildingInformation.h"


namespace MCF
{
  namespace Lua
  {
    namespace BuildingInformationScriptCommands
    {
      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        CelesteEngine::Lua::registerUserType<Buildings::BuildingInformation>(
          "BuildingInformation",
          "load", &CelesteEngine::Lua::loadScriptableObject<Buildings::BuildingInformation>);
      }
    }
  }
}