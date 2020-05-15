#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Events/Event.h"

#include <array>


namespace MCF::Persistence
{
  class DataStore;
}

namespace MCF::Time
{
  class TimeManager : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(TimeManager, MCFLibraryDllExport);

    public:
      using TimeEvent = Celeste::Event<>;

      MCFLibraryDllExport void update(float elapsedGameTime);

      MCFLibraryDllExport void setDataStore(observer_ptr<Persistence::DataStore> dataStore);

      float getSecondsPerDay() const { return m_secondsPerDay.getValue(); }
      MCFLibraryDllExport void setSecondsPerDay(float secondsPerDay);

      bool isPaused() const { return m_paused; }
      MCFLibraryDllExport void setPaused(bool isPaused);

      unsigned int getCurrentDay() const { return m_currentDay; }
      unsigned int getCurrentMonth() const { return m_currentMonth; }
      unsigned int getCurrentYear() const { return m_currentYear; }

      const Celeste::Event<float>& getOnTimePassedEvent() const { return m_onTimePassed; }
      const TimeEvent& getOnDayPassedEvent() const { return m_onDayPassed; }
      const TimeEvent& getOnMonthPassedEvent() const { return m_onMonthPassed; }
      const TimeEvent& getOnYearPassedEvent() const { return m_onYearPassed; }

      static const char* const SECONDS_PER_DAY_ATTRIBUTE_NAME;
      static const char* const TOTAL_DAYS_PASSED_ATTRIBUTE_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;
      void doSerialize(tinyxml2::XMLElement* element) const override;

    private:
      void updateDataStore() const;

      Celeste::ValueField<float>& m_secondsPerDay;

      observer_ptr<Persistence::DataStore> m_dataStore = nullptr;

      Celeste::Event<float> m_onTimePassed;
      TimeEvent m_onDayPassed;
      TimeEvent m_onMonthPassed;
      TimeEvent m_onYearPassed;

      float m_currentDayTimer = 0;
      unsigned int m_currentDay = 0;
      unsigned int m_currentMonth = 0;
      unsigned int m_currentYear = 0;
      bool m_paused = false;
  };
}