#include "Game/MCFGame.h"
#include "UtilityHeaders/PlatformHeaders.h"
#include "Persistence/DataStore.h"

// Disables console window
#if WINDOWS && !defined(__CYGWIN__)
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

// The MAIN function, from here we start the application and run the game loop
int main()
{
  MCF::MCFGame* game = new MCF::MCFGame();
  game->run();

  MCF::Persistence::DataStore dataStore;
  dataStore.hasData("Test");

  return 0;
}