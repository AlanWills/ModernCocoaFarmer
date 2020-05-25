#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"
#include "glm/glm.hpp"


namespace MCF::Data::Communication
{
  class Vec3ValueForwarder;
}

namespace MCF::DataConverters::Data::Communication
{
  class Vec3ValueForwarderDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(Vec3ValueForwarderDataConverter, MCF::Data::Communication::Vec3ValueForwarder, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}