#include "Game/MCFGame.h"
#include "UtilityHeaders/PlatformHeaders.h"

// Disables console window
#if WINDOWS && !defined(__CYGWIN__)
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

#include "Networking/SocketClient.h"
#include "Networking/SocketServer.h"

// The MAIN function, from here we start the application and run the game loop
int main()
{
  MCF::SocketClient client;
  //MCF::SocketServer server;

  while (true) {}

  /*MCF::MCFGame* game = new MCF::MCFGame();
  game->run();

  return 0;*/
}