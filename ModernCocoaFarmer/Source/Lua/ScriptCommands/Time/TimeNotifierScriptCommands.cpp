#include "Lua/ScriptCommands/Time/TimeNotifierScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

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
  void initialize()
  {
    Celeste::Lua::registerUserType<TimeNotifier>(
      "TimeNotifier",
      sol::base_classes, sol::bases<Celeste::Component, Celeste::Entity, Celeste::Object>(),
      "subscribeOnTimeChangedCallback", &subscribeOnTimeChangedCallback);
  }
}