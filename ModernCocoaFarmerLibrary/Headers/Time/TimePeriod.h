#pragma once

#include "Utils/ToString.h"


namespace MCF::Time
{
  enum class TimePeriod
  {
    kDay,
    kMonth,
    kYear
  };
}

namespace CelesteEngine
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Time::TimePeriod timePeriod);
}