#include "Lua/ScriptCommands/Time/TimeNotifierScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Time/TimeNotifier.h"

using namespace MCF::Time;


namespace MCF::Lua::Time::TimeNotifierScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void subscribeOnTimeChangedCallback(
    MCF::Time::TimeNotifier& timeNotifier,
    sol::function callback,
    sol::object extraArgs)
  {
    CelesteEngine::Lua::subscribeToEvent<TimeNotifier::TimeChangedEvent, float>(
      timeNotifier.getOnTimeChangedEvent(), callback, extraArgs);
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CelesteEngine::Lua::registerUserType<TimeNotifier>(
      "TimeNotifier",
      sol::base_classes, sol::bases<CelesteEngine::Script, CelesteEngine::Component, CelesteEngine::Entity, CelesteEngine::Object>(),
      "subscribeOnTimeChangedCallback", &subscribeOnTimeChangedCallback);
  }
}