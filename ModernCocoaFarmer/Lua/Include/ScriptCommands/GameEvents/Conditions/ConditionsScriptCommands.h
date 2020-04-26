#pragma once


namespace sol
{
  class state;
}

namespace MCF::Lua::GameEvents::Conditions::ScriptCommands
{
  void initialize(sol::state& state);
}