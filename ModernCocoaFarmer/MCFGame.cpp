#include "MCFGame.h"
#include "Lua/LuaState.h"
#include "Data/DataSystem.h"
#include "Dolce/IDolce.h"
#include "CelesteStl/Templates/Unused.h"
#include "Time/TimeNotifierSystem.h"

#include "ScriptCommands/Celeste/CelesteScriptCommands.h"
#include "ScriptCommands/MCFScriptCommands.h"

#if _DEBUG
#include "Debug/Windows/DataSystemDolceWindow.h"
#endif

using namespace Celeste;


namespace MCF
{
  //------------------------------------------------------------------------------------------------
  MCFGame::MCFGame()
  {
    addSystem<Data::DataSystem>();
    addSystem<Time::TimeNotifierSystem>();

    Path pathToResources = Path(Directory::getExecutingAppDirectory(), "ModernCocoaFarmer", "Resources");
    getResourceManager().setResourcesDirectory(pathToResources);

    Celeste::Lua::LuaState::appendToLuaPackagePath(
      Celeste::Path(Directory::getExecutingAppDirectory(), "Celeste", "Celeste", "Lua", "Resources", "Scripts", "?.lua;"));
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
#if _DEBUG
    dolce.addWindow(std::make_unique<Debug::DataSystemDolceWindow>(*getSystem<Data::DataSystem>()));
#else
    celstl::unused(dolce);
#endif
  }
}