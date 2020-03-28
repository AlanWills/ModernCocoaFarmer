#include "Time/TimeManager.h"
#include "Time/DataSources.h"
#include "Persistence/DataStore.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF::Time
{
  REGISTER_SCRIPTABLE_OBJECT(TimeManager);

  //------------------------------------------------------------------------------------------------
  const char* const TimeManager::SECONDS_PER_DAY_ATTRIBUTE_NAME = "seconds_per_day";
  
  //------------------------------------------------------------------------------------------------
  TimeManager::TimeManager() :
    m_secondsPerDay(createValueField<float>(SECONDS_PER_DAY_ATTRIBUTE_NAME, 1.0f)),
    m_onDayPassed(),
    m_onMonthPassed(),
    m_onYearPassed()
  {
  }

  //------------------------------------------------------------------------------------------------
  void TimeManager::update(float elapsedGameTime)
  {
    if (!m_paused)
    {
      m_currentDayTimer += elapsedGameTime;

      // In case our timestep is bigger than our seconds per day value
      while (m_currentDayTimer > m_secondsPerDay.getValue())
      {
        m_currentDayTimer -= m_secondsPerDay.getValue();
        ++m_currentDay;

        bool monthPassed = m_currentDay >= 30;
        if (monthPassed)
        {
          m_currentDay -= 30;
          ++m_currentMonth;
        }

        bool yearPassed = m_currentMonth >= 12;
        if (yearPassed)
        {
          m_currentMonth -= 12;
          ++m_currentYear;
        }
        
        m_onDayPassed.invoke();

        if (monthPassed)
        {
          m_onMonthPassed.invoke();
        }

        if (yearPassed)
        {
          m_onYearPassed.invoke();
        }

        updateDataStore();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void TimeManager::setDataStore(observer_ptr<Persistence::DataStore> dataStore)
  {
    m_dataStore = dataStore;
    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void TimeManager::updateDataStore() const
  {
    LOG("D/M/Y " + std::to_string(getCurrentDay()) + "/" + std::to_string(getCurrentMonth()) + "/" + std::to_string(getCurrentYear()));

    if (m_dataStore != nullptr)
    {
      m_dataStore->set(DataSources::CURRENT_MONTH, static_cast<unsigned int>(getCurrentMonth()));
    }
  }
}