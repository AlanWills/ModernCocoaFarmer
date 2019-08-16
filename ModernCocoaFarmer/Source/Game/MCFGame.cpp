#include "Game/MCFGame.h"
#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Screens/ScreenUtils.h"
#include "Debugging/SceneBroadcaster.h"
#include "Debugging/LuaScriptReceiver.h"


namespace MCF
{
  //------------------------------------------------------------------------------------------------
  MCFGame::MCFGame() :
    m_sceneBroadcaster(nullptr),
    m_luaScriptReceiver(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  void MCFGame::onInitialize()
  {
    Inherited::onInitialize();

    // Set up game specific script commands
    MCF::Lua::MCFScriptCommands::initialize();

    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0) {
      printf("WSAStartup failed with error: %d\n", result);
    }

    m_sceneBroadcaster.reset(new Debugging::SceneBroadcaster());
    m_sceneBroadcaster->start(*getScreenManager());

    m_luaScriptReceiver.reset(new Debugging::LuaScriptReceiver());
    m_luaScriptReceiver->start();
  }

  //------------------------------------------------------------------------------------------------
  void MCFGame::onUpdate(float elapsedGameTime)
  {
    m_sceneBroadcaster->update(*getScreenManager());
    m_luaScriptReceiver->update();
  }

  //------------------------------------------------------------------------------------------------
  void MCFGame::onExit()
  {
    m_sceneBroadcaster->stop();
    m_luaScriptReceiver->stop();
  }
}