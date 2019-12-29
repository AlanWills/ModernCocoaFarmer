#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/Script.h"
#include "Events/Event.h"


namespace MCF::Time
{
  class TimeNotifier : public CelesteEngine::Script
  {
    DECLARE_SCRIPT(TimeNotifier, MCFLibraryDllExport);

    public:
      const CelesteEngine::Event<float>& getOnTimeChangedEvent() const { return m_onTimeChangedEvent; }

    protected:
      void onUpdate(float elapsedGameTime) override;

    private:
      using Inherited = CelesteEngine::Script;

      CelesteEngine::Event<float> m_onTimeChangedEvent;
  };
}