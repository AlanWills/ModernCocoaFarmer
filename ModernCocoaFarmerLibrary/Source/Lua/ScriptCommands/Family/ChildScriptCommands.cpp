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
    void select(Child& child)
    {
      child.setSelected(true);
    }

    //------------------------------------------------------------------------------------------------
    void deselect(Child& child)
    {
      child.setSelected(false);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnSelectedChangedCallback(
      MCF::Family::Child& child,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<Child::OnSelectedChangedEvent, Child&, bool>(child.getOnSelectedChangedEvent(), callback, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CelesteEngine::Lua::registerScriptableObjectUserType<Child>(
      Child::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "getHealth", &Child::getHealth,
      "setHealth", &Child::setHealth,
      "getSafety", &Child::getSafety,
      "setSafety", &Child::setSafety,
      "getEducation", &Child::getEducation,
      "setEducation", &Child::setEducation,
      "getHappiness", &Child::getHappiness,
      "setHappiness", &Child::setHappiness,
      "isSelected", &Child::isSelected,
      "select", &Internals::select,
      "deselect", &Internals::deselect,
      "applyHealthModifier", &Child::applyHealthModifier,
      "applySafetyModifier", &Child::applySafetyModifier,
      "applyEducationModifier", &Child::applyEducationModifier,
      "applyHappinessModifier", &Child::applyHappinessModifier,
      "subscribeOnSelectedChangedCallback", &Internals::subscribeOnSelectedChangedCallback);
  }
}