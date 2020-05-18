#include "ScriptCommands/Data/DataSystemScriptCommands.h"
#include "Game/Game.h"
#include "Data/DataSystem.h"
#include "sol/sol.hpp"


namespace MCF::Lua::Data::DataSystemScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    MCF::Data::DataSystem* getDataSystem()
    {
      return Celeste::Game::current().getSystem<MCF::Data::DataSystem>();
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

    state.new_usertype<MCF::Data::DataSystem>(
      "DataSystem",
      sol::base_classes, sol::bases<MCF::Persistence::DataStore, Celeste::System::ISystem>());
  }
}