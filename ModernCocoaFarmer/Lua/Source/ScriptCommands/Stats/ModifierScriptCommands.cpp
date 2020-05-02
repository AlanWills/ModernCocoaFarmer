#include "ScriptCommands/Stats/ModifierScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Stats/Modifier.h"

using namespace MCF::Stats;


namespace sol
{
  template <>
  struct is_to_stringable<Modifier> : std::false_type {};
}

namespace MCF::Lua::Stats::ModifierScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void setChangeType(Modifier& modifier, const std::string& changeTypeString)
    {
      ChangeType changeType;
      if (Celeste::deserialize<ChangeType>(changeTypeString, changeType))
      {
        modifier.setChangeType(changeType);
      }
      else
      {
        ASSERT_FAIL();
      }
    }

    //------------------------------------------------------------------------------------------------
    bool isDeltaChange(MCF::Stats::Modifier& modifier)
    {
      return modifier.getChangeType() == MCF::Stats::ChangeType::kDelta;
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using Modifier = MCF::Stats::Modifier;

    Celeste::Lua::registerScriptableObjectUserType<Modifier>(
      state,
      "Modifier",
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "getAmount", &Modifier::getAmount,
      "setAmount", &Modifier::setAmount,
      "setChangeType", &Internals::setChangeType,
      "isDeltaChange", &Internals::isDeltaChange);
  }
}