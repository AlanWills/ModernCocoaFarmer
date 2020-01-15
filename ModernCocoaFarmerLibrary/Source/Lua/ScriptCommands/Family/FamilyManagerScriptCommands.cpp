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
      CelesteEngine::Lua::subscribeToEvent<FamilyManager::ChildAddedEvent, Child&>(
        familyManager.getChildAddedEvent(), 
        callback, 
        extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CelesteEngine::Lua::registerScriptableObjectUserType<FamilyManager>(
      FamilyManager::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "addChild", &FamilyManager::addChild,
      "getChildCount", &FamilyManager::getChildCount,
      "getChild", &FamilyManager::getChild,
      "selectOnlyThisChild", &FamilyManager::selectOnlyThisChild,
      "applyHealthModifier", &FamilyManager::applyHealthModifier,
      "applySafetyModifier", &FamilyManager::applySafetyModifier,
      "applyEducationModifier", &FamilyManager::applyEducationModifier,
      "applyHappinessModifier", &FamilyManager::applyHappinessModifier,
      "applyDailyModifiers", &FamilyManager::applyDailyModifiers,
      "subscribeOnChildAddedCallback", &Internals::subscribeOnChildAddedCallback);
  }
}