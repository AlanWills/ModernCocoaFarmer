#include "MCFGame.h"
#include "Lua/LuaState.h"
#include "Data/DataSystem.h"
#include "Debug/Windows/DataSystemDolceWindow.h"
#include "Dolce/IDolce.h"

#include "ScriptCommands/Celeste/CelesteScriptCommands.h"
#include "ScriptCommands/MCFScriptCommands.h"

using namespace Celeste;


namespace MCF
{
  //------------------------------------------------------------------------------------------------
  MCFGame::MCFGame()
  {
    addSystem<Data::DataSystem>();

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

  //------------------------------------------------------------------------------------------------
  void MCFGame::onInitializeDolce(Dolce::IDolce& dolce)
  {
    dolce.addWindow(std::make_unique<Debug::DataSystemDolceWindow>(*getSystem<Data::DataSystem>()));
  }
}