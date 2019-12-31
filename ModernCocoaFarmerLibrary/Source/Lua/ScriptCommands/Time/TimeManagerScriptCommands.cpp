#include "Lua/ScriptCommands/Time/TimeManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "Time/TimeManager.h"

using namespace MCF::Time;


namespace MCF::Lua::Time::TimeManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void pause(TimeManager& timeManager)
    {
      timeManager.setPaused(true);
    }

    //------------------------------------------------------------------------------------------------
    void play(TimeManager& timeManager)
    {
      timeManager.setPaused(false);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnDayPassedCallback(
      TimeManager& timeManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<TimeManager::TimeEvent>(timeManager.getOnDayPassedEvent(), callback, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnMonthPassedCallback(
      TimeManager& timeManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<TimeManager::TimeEvent>(timeManager.getOnMonthPassedEvent(), callback, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnYearPassedCallback(
      TimeManager& timeManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<TimeManager::TimeEvent>(timeManager.getOnYearPassedEvent(), callback, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CelesteEngine::Lua::registerScriptableObjectUserType<TimeManager>(
      TimeManager::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "getCurrentDay", &TimeManager::getCurrentDay,
      "getCurrentMonth", &TimeManager::getCurrentMonth,
      "getCurrentYear", &TimeManager::getCurrentYear,
      "pause", &Internals::pause,
      "play", &Internals::play,
      "isPaused", &TimeManager::isPaused,
      "update", &TimeManager::update,
      "subscribeOnDayPassedCallback", &Internals::subscribeOnDayPassedCallback,
      "subscribeOnMonthPassedCallback", &Internals::subscribeOnMonthPassedCallback,
      "subscribeOnYearPassedCallback", &Internals::subscribeOnYearPassedCallback);
  }
}