#include "Lua/ScriptCommands/Animation/ScriptCommands.h"
#include "Lua/ScriptCommands/Animation/ChildWalkingToLocationControllerScriptCommands.h"


namespace MCF::Lua::Animation::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    ChildWalkingToLocationControllerScriptCommands::initialize();
  }
}