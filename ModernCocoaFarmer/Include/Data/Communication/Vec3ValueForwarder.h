#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/Communication/ValueForwarder.h"
#include "glm/glm.hpp"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Communication
{
  class Vec3ValueForwarder : public ValueForwarder<glm::vec3>
  {
    DECLARE_MANAGED_COMPONENT(Vec3ValueForwarder, DataSystem, MCFLibraryDllExport);

    private:
      using Inherited = ValueForwarder<glm::vec3>;
  };
}