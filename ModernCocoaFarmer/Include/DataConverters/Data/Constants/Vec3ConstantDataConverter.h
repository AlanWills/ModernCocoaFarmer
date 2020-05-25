#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/Constants/ConstantDataConverter.h"
#include "glm/glm.hpp"


namespace MCF::Data
{
  class DataSystem;

  namespace Constants
  {
    class Vec3Constant;
  }
}

namespace MCF::DataConverters::Data::Constants
{
  class Vec3ConstantDataConverter : public ConstantDataConverter<glm::vec3>
  {
    DECLARE_COMPONENT_DATA_CONVERTER(Vec3ConstantDataConverter, MCF::Data::Constants::Vec3Constant, MCFLibraryDllExport);

    private:
      using Inherited = ConstantDataConverter<glm::vec3>;
  };
}