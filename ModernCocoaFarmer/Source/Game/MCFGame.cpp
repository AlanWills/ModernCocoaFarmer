#include "Game/MCFGame.h"
#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Screens/ScreenUtils.h"
#include "Debugging/SceneBroadcaster.h"


namespace MCF
{
  //------------------------------------------------------------------------------------------------
  MCFGame::MCFGame() :
    m_sceneBroadcaster(nullptr)
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
  }
}