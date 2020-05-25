#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/Constants/Constant.h"
#include "glm/glm.hpp"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Constants
{
  class Vec3Constant : public Constant<glm::vec3>
  {
    DECLARE_MANAGED_COMPONENT(Vec3Constant, DataSystem, MCFLibraryDllExport);

    private:
      using Inherited = Constant<glm::vec3>;
  };
}