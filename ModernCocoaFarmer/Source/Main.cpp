#include "stdafx.h"

#include "Game/Game.h"
#include "Lua/ScriptCommands/MCFScriptCommands.h"

// Disables console window
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
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