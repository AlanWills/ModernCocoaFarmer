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

    m_sceneBroadcaster.reset(new Debugging::SceneBroadcaster());
    m_sceneBroadcaster->startBroadcasting(*getScreenManager());

    m_luaScriptReceiver.reset(new Debugging::LuaScriptReceiver());
    m_luaScriptReceiver->start();
  }

  //------------------------------------------------------------------------------------------------
  void MCFGame::onUpdate(float elapsedGameTime)
  {
    m_luaScriptReceiver->update();
  }
}