#include "Lua/ScriptCommands/Animation/ChildWalkingToLocationControllerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Animation/ChildWalkingToLocationController.h"


namespace MCF::Lua::Animation::ChildWalkingToLocationControllerScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using ChildWalkingToLocationController = MCF::Animation::ChildWalkingToLocationController;

    Celeste::Lua::registerUserType<ChildWalkingToLocationController>(
      ChildWalkingToLocationController::type_name(),
      "getSpeed", &ChildWalkingToLocationController::getSpeed,
      "setSpeed", &ChildWalkingToLocationController::setSpeed,
      "getLocation", &ChildWalkingToLocationController::getLocation,
      "setLocation", &ChildWalkingToLocationController::setLocation);
  }
}