#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Conversion
{
  class ToString : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(ToString, DataSystem, MCFLibraryDllExport);

    public:
      void setType(size_t portType) { m_valuePort.setType(portType); }

      static const std::string VALUE_PORT_NAME;
      static const std::string OUTPUT_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onInputPortChanged(Persistence::Data&& newValue);

      InputPort& m_valuePort;
      OutputPort& m_outputPort;
  };
}