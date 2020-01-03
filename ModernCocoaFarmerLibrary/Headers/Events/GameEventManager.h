#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Memory/ObserverPtr.h"
#include "Events/Event.h"

namespace MCF::Family
{
  class FamilyManager;
}

namespace MCF::Time
{
  class TimeManager;
}

namespace MCF::Money
{
  class MoneyManager;
}


namespace MCF::Events
{
  class GameEvent;

  class GameEventManager : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(GameEventManager, MCFLibraryDllExport);

    public:
      using EventTriggeredEvent = CelesteEngine::Event<const GameEvent&>;

      void registerEvent(std::unique_ptr<GameEvent>& gameEvent);

      observer_ptr<Family::FamilyManager> getFamilyManager() const { return m_familyManager; }
      void setFamilyManager(observer_ptr<Family::FamilyManager> familyManager) { m_familyManager = familyManager; }

      observer_ptr<Time::TimeManager> getTimeManager() const { return m_timeManager; }
      void setTimeManager(observer_ptr<Time::TimeManager> timeManager);

      observer_ptr<Money::MoneyManager> getMoneyManager() const { return m_moneyManager; }
      void setMoneyManager(observer_ptr<Money::MoneyManager> moneyManager) { m_moneyManager = moneyManager; }

      const EventTriggeredEvent& getEventTriggeredEvent() const { return m_onEventTriggered; }

    private:
      void checkEventsForTriggering();

      observer_ptr<Family::FamilyManager> m_familyManager;
      observer_ptr<Time::TimeManager> m_timeManager;
      observer_ptr<Money::MoneyManager> m_moneyManager;

      std::vector<std::unique_ptr<const GameEvent>> m_events;
      EventTriggeredEvent m_onEventTriggered;

      CelesteEngine::StringId m_onDayPassedHandle;
      CelesteEngine::StringId m_onMonthPassedHandle;
      CelesteEngine::StringId m_onYearPassedHandle;
  };
}