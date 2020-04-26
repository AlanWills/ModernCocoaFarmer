#pragma once


namespace sol
{
  class state;
}

namespace MCF::Lua::Notifications::ScriptCommands
{
  void initialize(sol::state& state);
}