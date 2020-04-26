#pragma once


namespace sol
{
  class state;
}

namespace MCF::Lua::GameEvents::Conditions::LuaConditionScriptCommands
{
  void initialize(sol::state& state);
}