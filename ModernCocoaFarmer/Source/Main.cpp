#include "Game/Game.h"
#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "UtilityHeaders/PlatformHeaders.h"

// Disables console window
#if WINDOWS && !defined(__CYGWIN__)
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif


// The MAIN function, from here we start the application and run the game loop
int main()
{
  // Set up game specific script commands
  MCF::Lua::MCFScriptCommands::initialize();

  CelesteEngine::Game* game = new CelesteEngine::Game();
  game->run();
  
  return 0;
}