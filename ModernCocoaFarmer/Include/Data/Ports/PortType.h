#pragma once

#include "CelesteStl/Templates/Variant.h"
#include "Persistence/Data.h"


namespace MCF::Data
{
  template <typename T>
  struct PortType
  {
    using type = T;

    static constexpr size_t value() { return celstl::variant_index<Persistence::Data, T>(); }
  };
}