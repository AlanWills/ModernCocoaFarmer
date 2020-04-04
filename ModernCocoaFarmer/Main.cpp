#include "MCFGame.h"
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
  MCF::MCFGame game;
  game.getInputManager().getMouse().setCursor(Celeste::Path("Textures", "UI", "Utility", "Cursor.png"));
  game.run();

  return 0;
}