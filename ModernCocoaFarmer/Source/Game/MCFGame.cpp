#include "Game/MCFGame.h"
#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Scene/SceneUtils.h"
#include "Debugging/SceneBroadcaster.h"
#include "Debugging/LuaScriptReceiver.h"
#include "Networking/NetworkUtils.h"


namespace MCF
{
  //------------------------------------------------------------------------------------------------
  MCFGame::MCFGame() :
    m_sceneBroadcaster(nullptr),
    m_luaScriptReceiver(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  MCFGame::~MCFGame() = default;

  //------------------------------------------------------------------------------------------------
  void MCFGame::onInitialize()
  {
    Inherited::onInitialize();

    // Set up game specific script commands
    MCF::Lua::MCFScriptCommands::initialize();

    Celeste::Networking::initialize();

    m_sceneBroadcaster.reset(new Debugging::SceneBroadcaster());
    m_sceneBroadcaster->start();

    m_luaScriptReceiver.reset(new Debugging::LuaScriptReceiver());
    m_luaScriptReceiver->start();
  }

  //------------------------------------------------------------------------------------------------
  void MCFGame::onUpdate(float /*elapsedGameTime*/)
  {
    m_sceneBroadcaster->update(getSceneManager());
    m_luaScriptReceiver->update();
  }

  //------------------------------------------------------------------------------------------------
  void MCFGame::onExit()
  {
    m_sceneBroadcaster->stop();
    m_luaScriptReceiver->stop();

    Celeste::Networking::exit();
  }
}