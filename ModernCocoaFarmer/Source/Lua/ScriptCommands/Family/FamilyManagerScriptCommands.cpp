#include "Lua/ScriptCommands/Family/FamilyManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Family/FamilyManager.h"
#include "Family/Child.h"
#include "Stats/Modifier.h"

using namespace MCF::Family;


namespace MCF::Lua::Family::FamilyManagerScriptCommands
{
  namespace Internals
  {
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
  void initialize()
  {
    Celeste::Lua::registerScriptableObjectUserType<FamilyManager>(
      FamilyManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "setDataStore", &FamilyManager::setDataStore,
      "addChild", &FamilyManager::addChild,
      "getChildCount", &FamilyManager::getChildCount,
      "getChild", &FamilyManager::getChild,
      "hasSelectedChild", &FamilyManager::hasSelectedChild,
      "getSelectedChild", &FamilyManager::getSelectedChild,
      "selectOnlyThisChild", &FamilyManager::selectOnlyThisChild,
      "deselectOnlyThisChild", &FamilyManager::deselectOnlyThisChild,
      "applyHealthModifier", &FamilyManager::applyHealthModifier,
      "applySafetyModifier", &FamilyManager::applySafetyModifier,
      "applyEducationModifier", &FamilyManager::applyEducationModifier,
      "applyHappinessModifier", &FamilyManager::applyHappinessModifier,
      "applyDailyModifiers", &FamilyManager::applyDailyModifiers,
      "subscribeOnChildAddedCallback", &Internals::subscribeOnChildAddedCallback);
  }
}