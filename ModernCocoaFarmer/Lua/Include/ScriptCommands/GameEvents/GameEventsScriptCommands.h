#pragma once


namespace sol
{
  class state;
}

namespace MCF::Lua::GameEvents::ScriptCommands
{
  void initialize(sol::state& state);
}