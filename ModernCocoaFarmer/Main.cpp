#include "MCFGame.h"
#include "Platform/Platform.h"
#include "Debug/Logging/FileLogger.h"
#include "Log.h"

// Disables console window
#if WINDOWS && !defined(__CYGWIN__)
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

// The MAIN function, from here we start the application and run the game loop
int main()
{ 
  Celeste::Path logPath(Celeste::Directory::getExecutingAppDirectory(), "Log.txt");
  Celeste::Log::setLogger(std::make_unique<Celeste::FileLogger>(logPath));

  MCF::MCFGame game;
  game.run();

  return 0;
}