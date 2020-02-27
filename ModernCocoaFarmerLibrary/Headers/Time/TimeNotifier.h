#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/Script.h"
#include "Events/Event.h"


namespace MCF::Time
{
  class TimeNotifier : public Celeste::Script
  {
    DECLARE_SCRIPT(TimeNotifier, MCFLibraryDllExport);

    public:
      using TimeChangedEvent = Celeste::Event<float>;

      const TimeChangedEvent& getOnTimeChangedEvent() const { return m_onTimeChangedEvent; }

      MCFLibraryDllExport void update(float elapsedGameTime) override;

    private:
      using Inherited = Celeste::Script;

      TimeChangedEvent m_onTimeChangedEvent;
  };
}