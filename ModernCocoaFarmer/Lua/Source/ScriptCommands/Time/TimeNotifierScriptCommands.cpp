#include "ScriptCommands/Time/TimeNotifierScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Time/TimeNotifier.h"

using namespace MCF::Time;


namespace sol
{
  template <>
  struct is_to_stringable<MCF::Time::TimeNotifier> : std::false_type {};
}

namespace MCF::Lua::Time::TimeNotifierScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void subscribeOnTimeChangedCallback(
    MCF::Time::TimeNotifier& timeNotifier,
    sol::function callback,
    sol::object extraArgs)
  {
    Celeste::Lua::subscribeToEvent<TimeNotifier::TimeChangedEvent, float>(
      timeNotifier.getOnTimeChangedEvent(), callback, extraArgs);
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerUserType<TimeNotifier>(
      state,
      "TimeNotifier",
      sol::base_classes, sol::bases<Celeste::Component, Celeste::Entity, Celeste::Object>(),
      "subscribeOnTimeChangedCallback", &subscribeOnTimeChangedCallback);
  }
}