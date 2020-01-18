#include "Events/GameEventManager.h"
#include "Time/TimeManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Events/GameEvent.h"
#include "DataConverters/Objects/ScriptableObjectDataConverter.h"


namespace MCF::Events
{
  const char* const GameEventManager::GAME_EVENTS_ELEMENT_NAME = "GameEvents";
  const char* const GameEventManager::GAME_EVENT_ELEMENT_NAME = "GameEvent";

  //------------------------------------------------------------------------------------------------
  REGISTER_SCRIPTABLE_OBJECT(GameEventManager);

  //------------------------------------------------------------------------------------------------
  GameEventManager::GameEventManager() :
    m_familyManager(nullptr),
    m_timeManager(nullptr),
    m_moneyManager(nullptr),
    m_onGameEventTriggered(),
    m_gameEvents(),
    m_onDayPassedHandle(),
    m_onMonthPassedHandle(),
    m_onYearPassedHandle()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool GameEventManager::doDeserialize(const tinyxml2::XMLElement* element)
  {
    bool result = true;

    const tinyxml2::XMLElement* gameEventsElement = element->FirstChildElement(GAME_EVENTS_ELEMENT_NAME);
    if (gameEventsElement != nullptr)
    {
      for (const tinyxml2::XMLElement* gameEvent : children(gameEventsElement, GAME_EVENT_ELEMENT_NAME))
      {
        CelesteEngine::ScriptableObjectDataConverter gameEventDataConverter(gameEvent->Name());
        if (gameEventDataConverter.convertFromXML(gameEvent))
        {
          registerGameEvent(gameEventDataConverter.instantiate<GameEvent>());
        }
        else
        {
          ASSERT_FAIL();
          result = false;
        }
      }
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  void GameEventManager::registerGameEvent(std::unique_ptr<const GameEvent>&& gameEvent)
  {
    if (gameEvent == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    m_gameEvents.emplace_back(std::move(gameEvent));
  }

  //------------------------------------------------------------------------------------------------
  void GameEventManager::setFamilyManager(observer_ptr<Family::FamilyManager> familyManager)
  {
    m_familyManager = familyManager;
  }

  //------------------------------------------------------------------------------------------------
  void GameEventManager::setTimeManager(observer_ptr<Time::TimeManager> timeManager)
  {
    ASSERT(timeManager != nullptr);

    if (m_timeManager != nullptr)
    {
      m_timeManager->getOnDayPassedEvent().unsubscribe(m_onDayPassedHandle);
      m_timeManager->getOnMonthPassedEvent().unsubscribe(m_onMonthPassedHandle);
      m_timeManager->getOnYearPassedEvent().unsubscribe(m_onYearPassedHandle);
    }

    m_timeManager = timeManager;

    if (m_timeManager != nullptr)
    {
      m_onDayPassedHandle = m_timeManager->getOnDayPassedEvent().subscribe([this](CelesteEngine::EventArgs&) { checkEventsForTriggering(); });
      m_onMonthPassedHandle = m_timeManager->getOnMonthPassedEvent().subscribe([this](const CelesteEngine::EventArgs&) { checkEventsForTriggering(); });
      m_onYearPassedHandle = m_timeManager->getOnYearPassedEvent().subscribe([this](const CelesteEngine::EventArgs&) { checkEventsForTriggering(); });
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameEventManager::setMoneyManager(observer_ptr<Money::MoneyManager> moneyManager)
  {
    m_moneyManager = moneyManager;
  }

  //------------------------------------------------------------------------------------------------
  void GameEventManager::setLocationsManager(observer_ptr<Locations::LocationsManager> locationsManager)
  {
    m_locationsManager = locationsManager;
  }

  //------------------------------------------------------------------------------------------------
  void GameEventManager::checkEventsForTriggering()
  {
    for (const auto& event : m_gameEvents)
    {
      if (event->canTrigger(*m_timeManager, *m_moneyManager, *m_familyManager))
      {
        event->trigger(*m_moneyManager, *m_familyManager, *m_locationsManager);
        m_onGameEventTriggered.invoke(*event);
      }
    }
  }
}