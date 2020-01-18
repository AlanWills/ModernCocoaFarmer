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

namespace MCF::Locations
{
  class LocationsManager;
}

namespace MCF::Events
{
  class GameEvent;

  class GameEventManager : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(GameEventManager, MCFLibraryDllExport);

    public:
      using EventTriggeredEvent = CelesteEngine::Event<const GameEvent&>;

      void registerGameEvent(std::unique_ptr<const GameEvent>&& gameEvent);

      observer_ptr<Family::FamilyManager> getFamilyManager() const { return m_familyManager; }
      void setFamilyManager(observer_ptr<Family::FamilyManager> familyManager);

      observer_ptr<Time::TimeManager> getTimeManager() const { return m_timeManager; }
      void setTimeManager(observer_ptr<Time::TimeManager> timeManager);

      observer_ptr<Money::MoneyManager> getMoneyManager() const { return m_moneyManager; }
      void setMoneyManager(observer_ptr<Money::MoneyManager> moneyManager);

      observer_ptr<Locations::LocationsManager> getLocationsManager() const { return m_locationsManager; }
      void setLocationsManager(observer_ptr<Locations::LocationsManager> locationsManager);

      const EventTriggeredEvent& getGameEventTriggeredEvent() const { return m_onGameEventTriggered; }

      static const char* const GAME_EVENTS_ELEMENT_NAME;
      static const char* const GAME_EVENT_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      void checkEventsForTriggering();

      observer_ptr<Family::FamilyManager> m_familyManager;
      observer_ptr<Time::TimeManager> m_timeManager;
      observer_ptr<Money::MoneyManager> m_moneyManager;
      observer_ptr<Locations::LocationsManager> m_locationsManager;

      std::vector<std::unique_ptr<const GameEvent>> m_gameEvents;
      EventTriggeredEvent m_onGameEventTriggered;

      CelesteEngine::StringId m_onDayPassedHandle;
      CelesteEngine::StringId m_onMonthPassedHandle;
      CelesteEngine::StringId m_onYearPassedHandle;
  };
}