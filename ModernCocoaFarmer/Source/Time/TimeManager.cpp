#include "Time/TimeManager.h"
#include "Time/DataSources.h"
#include "Persistence/DataStore.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"

using namespace Celeste::XML;


namespace MCF::Time
{
  REGISTER_SCRIPTABLE_OBJECT(TimeManager);

  //------------------------------------------------------------------------------------------------
  const char* const TimeManager::SECONDS_PER_DAY_ATTRIBUTE_NAME = "seconds_per_day";
  const char* const TimeManager::TOTAL_DAYS_PASSED_ATTRIBUTE_NAME = "total_days_passed";
  
  const std::vector<std::string> MONTHS =
  {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December",
  };

  //------------------------------------------------------------------------------------------------
  TimeManager::TimeManager() :
    m_secondsPerDay(createValueField<float>(SECONDS_PER_DAY_ATTRIBUTE_NAME, 1.0f)),
    m_onTimePassed(),
    m_onDayPassed(),
    m_onMonthPassed(),
    m_onYearPassed()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool TimeManager::doDeserialize(const tinyxml2::XMLElement* element)
  {
    unsigned int totalDaysPassed = 0;
    XMLValueError result = getAttributeData(element, TOTAL_DAYS_PASSED_ATTRIBUTE_NAME, totalDaysPassed);

    if (result == XMLValueError::kSuccess)
    {
      m_currentYear = totalDaysPassed / 360;
      totalDaysPassed -= m_currentYear * 360;

      m_currentMonth = totalDaysPassed / 30;
      m_currentDay = totalDaysPassed - m_currentMonth * 30;
    }

    return result != XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  void TimeManager::doSerialize(tinyxml2::XMLElement* element) const
  {
    unsigned int totalDaysPassed = m_currentDay + m_currentMonth * 30 + m_currentYear * 360;
    element->SetAttribute(TOTAL_DAYS_PASSED_ATTRIBUTE_NAME, totalDaysPassed);
  }

  //------------------------------------------------------------------------------------------------
  void TimeManager::update(float elapsedGameTime)
  {
    if (!m_paused)
    {
      m_currentDayTimer += elapsedGameTime;
      
      // Fix the time to be inline with our changed scale for game time
      m_onTimePassed.invoke(elapsedGameTime / m_secondsPerDay.getValue());

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

        LOG("D/M/Y " + std::to_string(getCurrentDay()) + "/" + std::to_string(getCurrentMonth()) + "/" + std::to_string(getCurrentYear()));
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
    if (m_dataStore != nullptr)
    {
      m_dataStore->set(DataSources::CURRENT_MONTH, MONTHS[getCurrentMonth()]);
      m_dataStore->set(DataSources::IS_PAUSED, isPaused());
    }
  }

  //------------------------------------------------------------------------------------------------
  void TimeManager::setSecondsPerDay(float secondsPerDay)
  {
    if (secondsPerDay > 0)
    {
      m_secondsPerDay.setValue(secondsPerDay);
    }
  }

  //------------------------------------------------------------------------------------------------
  void TimeManager::setPaused(bool isPaused)
  {
    m_paused = isPaused;
    updateDataStore();
  }
}