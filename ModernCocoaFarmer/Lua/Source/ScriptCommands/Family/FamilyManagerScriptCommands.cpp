#include "ScriptCommands/Family/FamilyManagerScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "Stats/Modifier.h"

using namespace MCF::Family;


namespace sol
{
  template <>
  struct is_to_stringable<MCF::Family::FamilyManager> : std::false_type {};
}

namespace MCF::Lua::Family::FamilyManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void selectChild_StringOverload(FamilyManager& familyManager, const std::string& childName)
    {
      observer_ptr<Child> child = familyManager.findChild(childName);
      if (child != nullptr)
      {
        familyManager.selectChild(*child);
      }
    }

    //------------------------------------------------------------------------------------------------
    void deselectChild_StringOverload(FamilyManager& familyManager, const std::string& childName)
    {
      observer_ptr<Child> child = familyManager.findChild(childName);
      if (child != nullptr)
      {
        familyManager.deselectChild(*child);
      }
    }

    //------------------------------------------------------------------------------------------------
    void toggleChildSelection_StringOverload(FamilyManager& familyManager, const std::string& childName)
    {
      observer_ptr<Child> child = familyManager.findChild(childName);
      if (child != nullptr)
      {
        if (child->isSelected())
        {
          familyManager.deselectChild(*child);
        }
        else
        {
          familyManager.selectChild(*child);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnChildAddedCallback(
      MCF::Family::FamilyManager& familyManager,
      sol::function callback,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<FamilyManager::ChildAddedEvent, Child&>(
        familyManager.getChildAddedEvent(), 
        callback,
        extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerScriptableObjectUserType<FamilyManager>(
      state,
      FamilyManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "setDataSystem", &FamilyManager::setDataSystem,
      "canAddChild", &FamilyManager::canAddChild,
      "addChild", &FamilyManager::addChild,
      "getChildCount", &FamilyManager::getChildCount,
      "getChild", &FamilyManager::getChild,
      "findChild", &FamilyManager::findChild,
      "hasSelectedChild", &FamilyManager::hasSelectedChild,
      "getSelectedChild", &FamilyManager::getSelectedChild,
      "selectChild", sol::overload(&FamilyManager::selectChild, &Internals::selectChild_StringOverload),
      "deselectChild", sol::overload(&FamilyManager::deselectChild, &Internals::deselectChild_StringOverload),
      "toggleChildSelection", &Internals::toggleChildSelection_StringOverload,
      "applyHealthModifier", &FamilyManager::applyHealthModifier,
      "applySafetyModifier", &FamilyManager::applySafetyModifier,
      "applyEducationModifier", &FamilyManager::applyEducationModifier,
      "applyHappinessModifier", &FamilyManager::applyHappinessModifier,
      "applyDailyModifiers", &FamilyManager::applyDailyModifiers,
      "subscribeOnChildAddedCallback", &Internals::subscribeOnChildAddedCallback);
  }
}