#include "Lua/ScriptCommands/Stats/ChildModifierScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Stats/ChildModifier.h"


namespace MCF
{
  namespace Lua
  {
    namespace Stats
    {
      namespace ChildModifierScriptCommands
      {
        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          using ChildModifier = MCF::Stats::ChildModifier;

          CelesteEngine::Lua::registerScriptableObjectUserType<ChildModifier>(
            "ChildModifier",
            sol::base_classes, sol::bases<MCF::Stats::Modifier, CelesteEngine::ScriptableObject>(),
            "getAppliesToAllChildren", &ChildModifier::getAppliesToAllChildren);
        }
      }
    }
  }
}