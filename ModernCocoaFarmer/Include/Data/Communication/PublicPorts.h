#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Communication
{
  class PublicPorts : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(PublicPorts, DataSystem, MCFLibraryDllExport);
    
    public:
      InputPort& createInputPort(const std::string& name, size_t type, OutputPort& outputPort);
      OutputPort& createOutputPort(const std::string& name, size_t type);

    private:
      using Inherited = DataNodeComponent;
  };
}