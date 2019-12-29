#include "Lua/ScriptCommands/Time/TimeNotifierScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Time/TimeNotifier.h"


namespace MCF::Lua::Time::TimeNotifierScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void subscribeOnTimeChangedCallback(
      MCF::Time::TimeNotifier& timeNotifier,
      sol::function callback,
      sol::object extraArgs)
    {
      timeNotifier.getOnTimeChangedEvent().subscribe([callback, extraArgs](CelesteEngine::EventArgs& e, float deltaTime)
      {
          callback.call(e, deltaTime, extraArgs);
      });
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using TimeNotifier = MCF::Time::TimeNotifier;

    CelesteEngine::Lua::registerHandleUserType<TimeNotifier>(
      "TimeNotifier",
      sol::base_classes, sol::bases<CelesteEngine::Script, CelesteEngine::Component, CelesteEngine::Entity, CelesteEngine::Object>(),
      "subscribeOnTimeChangedCallback", &Internals::subscribeOnTimeChangedCallback);
  }
}