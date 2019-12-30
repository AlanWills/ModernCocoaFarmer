#include "Lua/ScriptCommands/Events/EventScriptCommands.h"
#include "Lua/ScriptCommands/Events/GameEventScriptCommands.h"


namespace MCF::Lua::Events::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    GameEventScriptCommands::initialize();
  }
}