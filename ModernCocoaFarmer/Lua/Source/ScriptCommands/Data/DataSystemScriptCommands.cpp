#include "ScriptCommands/Data/DataSystemScriptCommands.h"
#include "Data/DataUtils.h"
#include "Data/DataSystem.h"
#include "sol/sol.hpp"


namespace MCF::Lua::Data::DataSystemScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    if (!state["System"].valid())
    {
      state.create_named_table("System");
    }

    state["System"]["getDataSystem"] = &MCF::Data::getDataSystem;

    state.new_usertype<MCF::Data::DataSystem>(
      "DataSystem",
      sol::base_classes, sol::bases<MCF::Persistence::DataStore, Celeste::System::ISystem>());
  }
}