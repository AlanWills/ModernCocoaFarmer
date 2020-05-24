#pragma once

#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Communication
{
  class DataReader;
}

namespace MCF::DataConverters::Data::Communication
{
  class DataReaderDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(DataReaderDataConverter, MCF::Data::Communication::DataReader, MCFLibraryDllExport);

    public:
      size_t getType() const { return m_type.getValue(); }
      const std::string& getKey() const { return m_key.getValue(); }

      static const char* const TYPE_ATTRIBUTE_NAME;
      static const char* const KEY_ATTRIBUTE_NAME;

    private:
      using Inherited = DataNodeComponentDataConverter;

      Celeste::XML::ValueAttribute<size_t>& m_type;
      Celeste::XML::ReferenceAttribute<std::string>& m_key;
  };
}