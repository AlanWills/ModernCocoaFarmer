#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Conversion
{
  class ToString;
}

namespace MCF::DataConverters::Data::Conversion
{
  class ToStringDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(ToStringDataConverter, MCF::Data::Conversion::ToString, MCFLibraryDllExport);

    public:
      size_t getType() const { return m_type.getValue(); }

      static const char* const TYPE_ATTRIBUTE_NAME;

    private:
      using Inherited = DataNodeComponentDataConverter;

      Celeste::XML::ValueAttribute<size_t>& m_type;
  };
}