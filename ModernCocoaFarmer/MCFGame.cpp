#include "MCFGame.h"
#include "Lua/LuaState.h"
#include "Persistence/DataSystem.h"

#include "ScriptCommands/Celeste/CelesteScriptCommands.h"
#include "ScriptCommands/MCFScriptCommands.h"

using namespace Celeste;


namespace MCF
{
  //------------------------------------------------------------------------------------------------
  MCFGame::MCFGame()
  {
    addSystem<Persistence::DataSystem>();

    // Will need to make this for just VS
    Path pathToResources = Path(Directory::getExecutingAppDirectory(), UPDIR_STRING, UPDIR_STRING, UPDIR_STRING, "ModernCocoaFarmer", "Resources");
    getResourceManager().setResourcesDirectory(pathToResources);

    Celeste::Lua::LuaState::appendToLuaPackagePath(
      Celeste::Path(pathToResources, UPDIR_STRING, UPDIR_STRING, "Celeste", "Celeste", "Lua", "Resources", "Scripts", "?.lua;"));
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