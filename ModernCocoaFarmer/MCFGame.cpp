#include "MCFGame.h"
#include "Lua/LuaState.h"
#include "ScriptCommands/CelesteScriptCommands.h"
#include "ScriptCommands/MCFScriptCommands.h"


namespace MCF
{
  //------------------------------------------------------------------------------------------------
  MCFGame::MCFGame()
  {
    Celeste::Lua::LuaState::appendToLuaPackagePath(
      Celeste::Path(Celeste::Resources::getResourcesDirectory(), "..", "..", "Celeste", "CelesteLua", "Resources", "Scripts", "?.lua;"));
  }

  //------------------------------------------------------------------------------------------------
  MCFGame::~MCFGame() = default;

  //------------------------------------------------------------------------------------------------
  void MCFGame::onInitialize()
  {
    Inherited::onInitialize();

    sol::state& state = Celeste::Lua::LuaState::instance();

    Celeste::Lua::CelesteScriptCommands::initialize(state);
    MCF::Lua::MCFScriptCommands::initialize(state);
  }
}