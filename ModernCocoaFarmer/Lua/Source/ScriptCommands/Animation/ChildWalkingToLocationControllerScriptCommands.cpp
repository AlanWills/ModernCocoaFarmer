#include "ScriptCommands/Animation/ChildWalkingToLocationControllerScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "Animation/ChildWalkingToLocationController.h"


namespace sol
{
  template <>
  struct is_to_stringable<MCF::Animation::ChildWalkingToLocationController> : std::false_type {};
}

namespace MCF::Lua::Animation::ChildWalkingToLocationControllerScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using ChildWalkingToLocationController = MCF::Animation::ChildWalkingToLocationController;

    Celeste::Lua::registerUserType<ChildWalkingToLocationController>(
      state,
      ChildWalkingToLocationController::type_name(),
      "getSpeed", &ChildWalkingToLocationController::getSpeed,
      "setSpeed", &ChildWalkingToLocationController::setSpeed,
      "getLocation", &ChildWalkingToLocationController::getLocation,
      "setLocation", &ChildWalkingToLocationController::setLocation);
  }
}