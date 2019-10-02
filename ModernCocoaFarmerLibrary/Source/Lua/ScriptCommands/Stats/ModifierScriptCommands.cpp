#include "Lua/ScriptCommands/Stats/ModifierScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Stats/Modifier.h"


namespace MCF
{
  namespace Lua
  {
    namespace Stats
    {
      namespace ModifierScriptCommands
      {
        namespace Internals
        {
          //------------------------------------------------------------------------------------------------
          bool isDeltaChange(MCF::Stats::Modifier& modifier)
          {
            return modifier.getChangeType() == MCF::Stats::ChangeType::kDelta;
          }

          //------------------------------------------------------------------------------------------------
          bool isPeriodicChange(MCF::Stats::Modifier& modifier)
          {
            return modifier.getOccurrence() == MCF::Stats::Occurrence::kPeriodic;
          }
        }

        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          using Modifier = MCF::Stats::Modifier;

          CelesteEngine::Lua::registerScriptableObjectUserType<Modifier>(
            "Modifier",
            sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
            "getAmount", &Modifier::getAmount,
            "isDeltaChange", &Internals::isDeltaChange,
            "isPeriodicChange", &Internals::isPeriodicChange,
            "getMonthlyFrequency", &Modifier::getMonthlyFrequency);
        }
      }
    }
  }
}