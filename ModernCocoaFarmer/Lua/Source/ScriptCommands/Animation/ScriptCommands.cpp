#include "ScriptCommands/Animation/ScriptCommands.h"
#include "ScriptCommands/Animation/ChildWalkingToLocationControllerScriptCommands.h"


namespace MCF::Lua::Animation::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    ChildWalkingToLocationControllerScriptCommands::initialize(state);
  }
}