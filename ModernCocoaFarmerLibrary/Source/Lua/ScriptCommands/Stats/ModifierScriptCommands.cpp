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
        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          using Modifier = MCF::Stats::Modifier;

          CelesteEngine::Lua::registerScriptableObjectUserType<Modifier>(
            "Modifier",
            sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
            "getDescription", &BuildingInformation::getDescription,
            "getHealthModifier", &BuildingInformation::getHealthModifier,
            "getSafetyModifier", &BuildingInformation::getSafetyModifier,
            "getEducationModifier", &BuildingInformation::getEducationModifier,
            "getHappinessModifier", &BuildingInformation::getHappinessModifier,
            "getMoneyModifier", &BuildingInformation::getMoneyModifier,
            "getMonthsToComplete", &BuildingInformation::getMonthsToComplete);
        }
      }
    }
  }
}