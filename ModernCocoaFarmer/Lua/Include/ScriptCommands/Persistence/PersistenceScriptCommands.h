#pragma once


namespace sol
{
  class state;
}

namespace MCF::Lua::Persistence::ScriptCommands
{
  void initialize(sol::state& state);
}