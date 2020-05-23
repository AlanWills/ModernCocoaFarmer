#pragma once

#include "DataConverters/Data/Communication/DataReaderDataConverter.h"


namespace MCF::DataConverters::Data::Communication
{
  class StringDataReaderDataConverter : public DataReaderDataConverter<std::string>
  {
    DECLARE_COMPONENT_DATA_CONVERTER(StringDataReaderDataConverter, MCF::Data::Communication::StringDataReader, MCFLibraryDllExport);

    private:
      using Inherited = DataReaderDataConverter<std::string>;
  };
}