#include "ScriptCommands/Family/ChildScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Family/Child.h"
#include "Stats/Modifier.h"

using namespace MCF::Family;


namespace sol
{
  template <>
  struct is_to_stringable<MCF::Family::Child> : std::false_type {};
}

namespace MCF::Lua::Family::ChildScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerScriptableObjectUserType<Child>(
      state,
      Child::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "getHealth", &Child::getHealth,
      "setHealth", &Child::setHealth,
      "getSafety", &Child::getSafety,
      "setSafety", &Child::setSafety,
      "getEducation", &Child::getEducation,
      "setEducation", &Child::setEducation,
      "getHappiness", &Child::getHappiness,
      "setHappiness", &Child::setHappiness,
      "applyHealthModifier", &Child::applyHealthModifier,
      "applySafetyModifier", &Child::applySafetyModifier,
      "applyEducationModifier", &Child::applyEducationModifier,
      "applyHappinessModifier", &Child::applyHappinessModifier,
      "isAtLocation", &Child::isAtLocation,
      "getCurrentLocation", &Child::getCurrentLocation,
      "getTimeAtLocation", &Child::getTimeAtLocation,
      "setTimeAtLocation", &Child::setTimeAtLocation,
      "incrementTimeAtLocation", &Child::incrementTimeAtLocation,
      "isNotBorn", &Child::isNotBorn,
      "isActivated", &Child::isActivated,
      "canGraduate", &Child::canGraduate,
      "isGraduated", &Child::isGraduated,
      "graduate", &Child::graduate,
      "canDie", &Child::canDie,
      "isDead", &Child::isDead,
      "die", &Child::die,
      "isSelected", &Child::isSelected);
  }
}