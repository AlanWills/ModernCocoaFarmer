#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::UI
{
  class ProgressBarController : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(ProgressBarController, DataSystem, MCFLibraryDllExport);

    public:
      static const std::string PROGRESS_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onProgressPortChanged(Persistence::Data&& newValue);

      InputPort& m_progressPort;
  };
}