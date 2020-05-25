#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Logic
{
  class Not;
}

namespace MCF::DataConverters::Data::Logic
{
  class NotDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(NotDataConverter, MCF::Data::Logic::Not, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}