#include "Lua/ScriptCommands/Stats/ChildModifierScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Stats/ChildModifier.h"


namespace MCF::Lua::Stats::ChildModifierScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using ChildModifier = MCF::Stats::ChildModifier;

    Celeste::Lua::registerScriptableObjectUserType<ChildModifier>(
      "ChildModifier",
      sol::base_classes, sol::bases<MCF::Stats::Modifier, Celeste::ScriptableObject>(),
      "getAppliesToAllChildren", &ChildModifier::getAppliesToAllChildren);
  }
}