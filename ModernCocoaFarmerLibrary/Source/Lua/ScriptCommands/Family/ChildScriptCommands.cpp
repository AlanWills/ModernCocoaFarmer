#include "Lua/ScriptCommands/Family/ChildScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Family/Child.h"
#include "Stats/Modifier.h"

using namespace MCF::Family;


namespace MCF::Lua::Family::ChildScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void subscribeOnSelectedChangedCallback(
      MCF::Family::Child& child,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<Child::OnSelectedChangedEvent, Child&>(child.getOnSelectedChangedEvent(), callback, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    Celeste::Lua::registerScriptableObjectUserType<Child>(
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
      "isSelected", &Child::isSelected,
      "subscribeOnSelectedChangedCallback", &Internals::subscribeOnSelectedChangedCallback);
  }
}