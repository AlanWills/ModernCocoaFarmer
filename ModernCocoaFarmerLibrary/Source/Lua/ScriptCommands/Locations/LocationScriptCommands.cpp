#include "Lua/ScriptCommands/Locations/LocationScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Locations/Location.h"
#include "Family/Child.h"


namespace MCF::Lua::Locations::LocationScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using Location = MCF::Locations::Location;

    CelesteEngine::Lua::registerScriptableObjectUserType<Location>(
      "LocationInformation",
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "getPrefab", &Location::getPrefab,
      "getDescription", &Location::getDescription,
      "getHealthModifier", &Location::getHealthModifier,
      "getSafetyModifier", &Location::getSafetyModifier,
      "getEducationModifier", &Location::getEducationModifier,
      "getHappinessModifier", &Location::getHappinessModifier,
      "getMoneyModifier", &Location::getMoneyModifier,
      "getDaysToComplete", &Location::getDaysToComplete,
      "sendChild", &Location::sendChild);
  }
}