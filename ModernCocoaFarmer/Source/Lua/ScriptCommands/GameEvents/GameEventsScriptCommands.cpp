#include "Lua/ScriptCommands/GameEvents/GameEventsScriptCommands.h"
#include "Lua/ScriptCommands/GameEvents/GameEventManagerScriptCommands.h"
#include "Lua/ScriptCommands/GameEvents/GameEventScriptCommands.h"


namespace MCF::Lua::GameEvents::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    GameEventManagerScriptCommands::initialize();
    GameEventScriptCommands::initialize();
  }
}