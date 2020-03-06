#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Events/Event.h"

#include <array>


namespace MCF::Time
{
  class TimeManager : public Celeste::ScriptableObject
  {
    DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(TimeManager, MCFLibraryDllExport);

    public:
      using TimeEvent = Celeste::Event<>;

      void update(float elapsedGameTime);

      bool isPaused() const { return m_paused; }
      void setPaused(bool isPaused) { m_paused = isPaused; }

      size_t getCurrentDay() const { return m_currentDay; }
      size_t getCurrentMonth() const { return m_currentMonth; }
      size_t getCurrentYear() const { return m_currentYear; }

      const TimeEvent& getOnDayPassedEvent() const { return m_onDayPassed; }
      const TimeEvent& getOnMonthPassedEvent() const { return m_onMonthPassed; }
      const TimeEvent& getOnYearPassedEvent() const { return m_onYearPassed; }

      static const char* const SECONDS_PER_DAY_ATTRIBUTE_NAME;

    private:
      Celeste::ValueField<float>& m_secondsPerDay;

      TimeEvent m_onDayPassed;
      TimeEvent m_onMonthPassed;
      TimeEvent m_onYearPassed;

      float m_currentDayTimer = 0;
      size_t m_currentDay = 0;
      size_t m_currentMonth = 0;
      size_t m_currentYear = 0;
      bool m_paused = false;
  };
}