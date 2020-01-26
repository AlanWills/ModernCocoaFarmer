#include "Lua/ScriptCommands/Locations/LocationScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Locations/Location.h"
#include "Family/Child.h"


using Location = MCF::Locations::Location;

namespace MCF::Lua::Locations::LocationScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void subscribeOnChildSentCallback(
      Location& location,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<Location::ChildSentEvent, const Family::Child&>(
        location.getOnChildSentEvent(), callback, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnChildLeftCallback(
      Location& location,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<Location::ChildLeftEvent, const Family::Child&>(
        location.getOnChildLeftEvent(), callback, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
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
      "sendChild", &Location::sendChild,
      "subscribeOnChildSentCallback", &Internals::subscribeOnChildSentCallback,
      "subscribeOnChildLeftCallback", &Internals::subscribeOnChildLeftCallback);
  }
}