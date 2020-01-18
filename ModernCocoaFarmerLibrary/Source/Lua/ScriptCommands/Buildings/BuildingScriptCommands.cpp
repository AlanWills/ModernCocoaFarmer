#include "Lua/ScriptCommands/Buildings/BuildingScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Buildings/Building.h"
#include "Family/Child.h"


namespace MCF::Lua::Buildings::BuildingScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using Building = MCF::Buildings::Building;

    CelesteEngine::Lua::registerScriptableObjectUserType<Building>(
      "BuildingInformation",
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "getPrefab", &Building::getPrefab,
      "getDescription", &Building::getDescription,
      "getHealthModifier", &Building::getHealthModifier,
      "getSafetyModifier", &Building::getSafetyModifier,
      "getEducationModifier", &Building::getEducationModifier,
      "getHappinessModifier", &Building::getHappinessModifier,
      "getMoneyModifier", &Building::getMoneyModifier,
      "getMonthsToComplete", &Building::getMonthsToComplete,
      "sendChild", &Building::sendChild);
  }
}