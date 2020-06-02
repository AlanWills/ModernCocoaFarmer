#pragma once

#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Communication
{
  class DataObjectKey;
}

namespace MCF::DataConverters::Data::Communication
{
  class DataObjectKeyDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(DataObjectKeyDataConverter, MCF::Data::Communication::DataObjectKey, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}