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

namespace MCF::Notifications
{
  class NotificationManager;
}

namespace MCF::Events
{
  class GameEvent;

  class GameEventManager : public Celeste::ScriptableObject
  {
    DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(GameEventManager, MCFLibraryDllExport);

    public:
      using GameEventTriggeredEvent = Celeste::Event<const GameEvent&>;

      void registerGameEvent(std::unique_ptr<const GameEvent>&& gameEvent);

      observer_ptr<Family::FamilyManager> getFamilyManager() const { return m_familyManager; }
      void setFamilyManager(observer_ptr<Family::FamilyManager> familyManager);

      observer_ptr<Time::TimeManager> getTimeManager() const { return m_timeManager; }
      void setTimeManager(observer_ptr<Time::TimeManager> timeManager);

      observer_ptr<Money::MoneyManager> getMoneyManager() const { return m_moneyManager; }
      void setMoneyManager(observer_ptr<Money::MoneyManager> moneyManager);

      observer_ptr<Locations::LocationsManager> getLocationsManager() const { return m_locationsManager; }
      void setLocationsManager(observer_ptr<Locations::LocationsManager> locationsManager);

      observer_ptr<Notifications::NotificationManager> getNotificationManager() const { return m_notificationManager; }
      void setNotificationManager(observer_ptr<Notifications::NotificationManager> notificationManager);

      const GameEventTriggeredEvent& getGameEventTriggeredEvent() const { return m_onGameEventTriggeredEvent; }

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
      observer_ptr<Notifications::NotificationManager> m_notificationManager;

      std::vector<std::unique_ptr<const GameEvent>> m_gameEvents;
      GameEventTriggeredEvent m_onGameEventTriggeredEvent;

      Celeste::StringId m_onDayPassedHandle;
  };
}