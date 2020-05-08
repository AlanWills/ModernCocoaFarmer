#include "ScriptCommands/Persistence/DataSystemScriptCommands.h"
#include "Game/Game.h"
#include "Persistence/DataSystem.h"
#include "sol/sol.hpp"


namespace MCF::Lua::Persistence::DataSystemScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    MCF::Persistence::DataSystem* getDataSystem()
    {
      return Celeste::Game::current().getSystem<MCF::Persistence::DataSystem>();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    if (!state["System"].valid())
    {
      state.create_named_table("System");
    }

    state["System"]["getDataSystem"] = &Internals::getDataSystem;

    state.new_usertype<MCF::Persistence::DataSystem>(
      "DataSystem",
      sol::base_classes, sol::bases<MCF::Persistence::DataStore, Celeste::System::ISystem>());
  }
}