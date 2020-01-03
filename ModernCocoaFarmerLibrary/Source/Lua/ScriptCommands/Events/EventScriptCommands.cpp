#include "Lua/ScriptCommands/Events/EventScriptCommands.h"
#include "Lua/ScriptCommands/Events/EventManagerScriptCommands.h"
#include "Lua/ScriptCommands/Events/GameEventScriptCommands.h"


namespace MCF::Lua::Events::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    EventManagerScriptCommands::initialize();
    GameEventScriptCommands::initialize();
  }
}