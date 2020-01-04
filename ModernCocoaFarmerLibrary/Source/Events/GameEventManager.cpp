#include "Events/GameEventManager.h"
#include "Time/TimeManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Events/GameEvent.h"


namespace MCF::Events
{
  REGISTER_SCRIPTABLE_OBJECT(GameEventManager);

  //------------------------------------------------------------------------------------------------
  GameEventManager::GameEventManager() :
    m_familyManager(nullptr),
    m_timeManager(nullptr),
    m_moneyManager(nullptr),
    m_onEventTriggered(),
    m_events(),
    m_onDayPassedHandle(),
    m_onMonthPassedHandle(),
    m_onYearPassedHandle()
  {
  }

  //------------------------------------------------------------------------------------------------
  void GameEventManager::registerEvent(std::unique_ptr<GameEvent>& gameEvent)
  {
    if (gameEvent == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    m_events.push_back(std::unique_ptr<const GameEvent>(gameEvent.release()));
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
  void GameEventManager::checkEventsForTriggering()
  {
    for (const auto& event : m_events)
    {
      if (event->canTrigger(*m_timeManager))
      {
        event->trigger(*m_timeManager);
      }
    }
  }
}