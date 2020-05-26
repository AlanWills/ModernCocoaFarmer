#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Logic
{
  class Not : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(Not, DataSystem, MCFLibraryDllExport)

    public:
      static const std::string INPUT_PORT_NAME;
      static const std::string OUTPUT_PORT_NAME;

  private:
      using Inherited = DataNodeComponent;

      void onInputChanged(Persistence::Data&& newValue);

      InputPort& m_inputPort;
      OutputPort& m_outputPort;
  };
}