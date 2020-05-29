#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/Component.h"
#include "Events/Event.h"


namespace MCF::Time
{
  class TimeNotifier : public Celeste::Component
  {
    DECLARE_UNMANAGED_COMPONENT(TimeNotifier, MCFLibraryDllExport);

    public:
      using TimeChangedEvent = Celeste::Event<float>;

      const TimeChangedEvent& getOnTimeChangedEvent() const { return m_onTimeChangedEvent; }

      MCFLibraryDllExport void update() override;

    private:
      using Inherited = Celeste::Component;

      TimeChangedEvent m_onTimeChangedEvent;
  };
}