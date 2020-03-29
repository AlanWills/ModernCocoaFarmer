#include "Game/MCFGame.h"
#include "Lua/LuaState.h"
#include "Lua/ScriptCommands/MCFScriptCommands.h"


namespace MCF
{
  //------------------------------------------------------------------------------------------------
  MCFGame::MCFGame()
  {
#if _DEBUG
    Celeste::Lua::LuaState::appendToLuaPackagePath(
      Celeste::Path(Celeste::Resources::getResourcesDirectory(), "..", "..", "Celeste", "Celeste", "Resources", "Scripts", "?.lua;"));
#endif
  }

  //------------------------------------------------------------------------------------------------
  MCFGame::~MCFGame() = default;

  //------------------------------------------------------------------------------------------------
  void MCFGame::onInitialize()
  {
    Inherited::onInitialize();

    // Set up game specific script commands
    MCF::Lua::MCFScriptCommands::initialize();
  }
}