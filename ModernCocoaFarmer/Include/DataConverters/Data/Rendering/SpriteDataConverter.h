#pragma once

#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Rendering
{
  class Sprite;
}

namespace MCF::DataConverters::Data::Rendering
{
  class SpriteDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(SpriteDataConverter, MCF::Data::Rendering::Sprite, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}