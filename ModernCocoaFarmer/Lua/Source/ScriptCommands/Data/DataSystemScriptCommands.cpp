#include "ScriptCommands/Data/DataSystemScriptCommands.h"
#include "Data/DataUtils.h"
#include "Data/DataSystem.h"
#include "sol/sol.hpp"


namespace MCF::Lua::Data::DataSystemScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    template <typename T>
    T get(MCF::Data::DataSystem& dataSystem, const char* const key)
    {
      return dataSystem.get<T>(key, T());
    }
  }

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
      sol::base_classes, sol::bases<Celeste::System::ISystem>(),
      "getBool", &Internals::get<bool>,
      "getInt", &Internals::get<int>,
      "getUInt", &Internals::get<unsigned int>,
      "getFloat", &Internals::get<float>,
      "getString", &Internals::get<std::string>,
      "getObject", &MCF::Data::DataSystem::getObject,
      "getArray", &MCF::Data::DataSystem::getArray);
  }
}