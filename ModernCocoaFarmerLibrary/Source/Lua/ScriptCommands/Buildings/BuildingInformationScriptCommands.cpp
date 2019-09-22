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
        using BuildingInformation = Buildings::BuildingInformation;

        CelesteEngine::Lua::registerScriptableObjectUserType<BuildingInformation>(
          "BuildingInformation",
          sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
          "getDescription", &BuildingInformation::getDescription,
          "getHealthModifier", &BuildingInformation::getHealthModifier,
          "getSafetyModifier", &BuildingInformation::getSafetyModifier,
          "getEducationModifier", &BuildingInformation::getEducationModifier,
          "getHappinessModifier", &BuildingInformation::getHappinessModifier,
          "getCostModifier", &BuildingInformation::getCostModifier,
          "getMonthsToComplete", &BuildingInformation::getMonthsToComplete);
      }
    }
  }
}