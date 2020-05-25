#pragma once

#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Rendering
{
  class Text;
}

namespace MCF::DataConverters::Data::Rendering
{
  class TextDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(TextDataConverter, MCF::Data::Rendering::Text, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}