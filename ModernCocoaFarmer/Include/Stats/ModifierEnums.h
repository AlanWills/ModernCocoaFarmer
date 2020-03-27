#pragma once

#include "Utils/ToString.h"

#include <string>


namespace MCF::Stats
{
  enum class ChangeType
  {
    kDelta,
    kAbsolute
  };
}

namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Stats::ChangeType changeType);
}