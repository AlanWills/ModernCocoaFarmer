#include "Lua/ScriptCommands/Stats/ModifierScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Stats/Modifier.h"


namespace MCF::Lua::Stats::ModifierScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    bool isDeltaChange(MCF::Stats::Modifier& modifier)
    {
      return modifier.getChangeType() == MCF::Stats::ChangeType::kDelta;
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using Modifier = MCF::Stats::Modifier;

    Celeste::Lua::registerScriptableObjectUserType<Modifier>(
      "Modifier",
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "getAmount", &Modifier::getAmount,
      "isDeltaChange", &Internals::isDeltaChange);
  }
}