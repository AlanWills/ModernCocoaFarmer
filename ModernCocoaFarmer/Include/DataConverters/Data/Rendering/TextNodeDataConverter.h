#pragma once

#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Rendering
{
  class TextNode;
}

namespace MCF::DataConverters::Data::Rendering
{
  class TextNodeDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(TextNodeDataConverter, MCF::Data::Rendering::TextNode, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}