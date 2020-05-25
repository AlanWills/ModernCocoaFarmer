#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"
#include "glm/glm.hpp"


namespace MCF::Data::Communication
{
  class ValueForwarder;
}

namespace MCF::DataConverters::Data::Communication
{
  class ValueForwarderDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(ValueForwarderDataConverter, MCF::Data::Communication::ValueForwarder, MCFLibraryDllExport);

    size_t getType() const { return m_type.getValue(); }

    static const char* const TYPE_ATTRIBUTE_NAME;

    private:
      using Inherited = DataNodeComponentDataConverter;

      Celeste::XML::ValueAttribute<size_t>& m_type;
  };
}