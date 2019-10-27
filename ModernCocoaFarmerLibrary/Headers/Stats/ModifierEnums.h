#pragma once

#include "Utils/ToString.h"

#include <string>


namespace MCF
{
  namespace Stats
  {
    enum class ChangeType
    {
      kDelta,
      kAbsolute
    };

    enum class Occurrence
    {
      kInstant,
      kPeriodic
    };
  }
}

namespace CelesteEngine
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Stats::ChangeType changeType);

  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Stats::Occurrence occurrence);
}