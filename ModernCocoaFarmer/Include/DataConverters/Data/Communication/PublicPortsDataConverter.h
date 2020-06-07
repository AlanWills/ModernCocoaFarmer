#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Communication
{
  class PublicPorts;
}

namespace MCF::DataConverters::Data::Communication
{
  class PublicPortsDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(PublicPortsDataConverter, MCF::Data::Communication::PublicPorts, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}