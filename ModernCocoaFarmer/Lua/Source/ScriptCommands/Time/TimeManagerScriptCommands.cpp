#include "ScriptCommands/Time/TimeManagerScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "Time/TimeManager.h"

using namespace MCF::Time;


namespace sol
{
  template <>
  struct is_to_stringable<TimeManager> : std::false_type {};
}

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
    void subscribeOnTimePassedCallback(
      TimeManager& timeManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<Celeste::Event<float>, float>(timeManager.getOnTimePassedEvent(), callback, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnDayPassedCallback(
      TimeManager& timeManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent(timeManager.getOnDayPassedEvent(), callback, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnMonthPassedCallback(
      TimeManager& timeManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent(timeManager.getOnMonthPassedEvent(), callback, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnYearPassedCallback(
      TimeManager& timeManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent(timeManager.getOnYearPassedEvent(), callback, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerScriptableObjectUserType<TimeManager>(
      state,
      TimeManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "setDataStore", &TimeManager::setDataStore,
      "getCurrentDay", &TimeManager::getCurrentDay,
      "getCurrentMonth", &TimeManager::getCurrentMonth,
      "getCurrentYear", &TimeManager::getCurrentYear,
      "pause", &Internals::pause,
      "play", &Internals::play,
      "isPaused", &TimeManager::isPaused,
      "update", &TimeManager::update,
      "subscribeOnTimePassedCallback", &Internals::subscribeOnTimePassedCallback,
      "subscribeOnDayPassedCallback", &Internals::subscribeOnDayPassedCallback,
      "subscribeOnMonthPassedCallback", &Internals::subscribeOnMonthPassedCallback,
      "subscribeOnYearPassedCallback", &Internals::subscribeOnYearPassedCallback);
  }
}