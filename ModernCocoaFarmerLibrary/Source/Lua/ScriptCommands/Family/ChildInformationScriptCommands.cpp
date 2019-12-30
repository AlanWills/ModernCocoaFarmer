#include "Lua/ScriptCommands/Family/ChildInformationScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Family/ChildInformation.h"


namespace MCF::Lua::Family::ChildInformationScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using ChildInformation = MCF::Family::ChildInformation;

    CelesteEngine::Lua::registerScriptableObjectUserType<ChildInformation>(
      "ChildInformation",
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "getHealth", &ChildInformation::getHealth,
      "setHealth", &ChildInformation::setHealth,
      "getSafety", &ChildInformation::getSafety,
      "getEducation", &ChildInformation::getEducation,
      "getHappiness", &ChildInformation::getHappiness);
  }
}