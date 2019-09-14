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
        CelesteEngine::Lua::registerScriptableObjectUserType<Buildings::BuildingInformation>(
          "BuildingInformation",
          sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
          "getDescription", &Buildings::BuildingInformation::getDescription);
      }
    }
  }
}