#pragma once

#include "MCFLibraryDllExport.h"

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
  MCFLibraryDllExport std::string to_string(MCF::Stats::ChangeType changeType);

  //------------------------------------------------------------------------------------------------
  MCFLibraryDllExport std::string to_string(MCF::Stats::Occurrence occurrence);
}