#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Animation
{
  class AnimatorController : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(AnimatorController, DataSystem, MCFLibraryDllExport);

    public:
      static const std::string PLAY_PORT_NAME;
      static const std::string STOP_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onPlayPortChanged(Persistence::Data&& newValue);
      void onStopPortChanged(Persistence::Data&& newValue);

      InputPort& m_playPort;
      InputPort& m_stopPort;
  };
}