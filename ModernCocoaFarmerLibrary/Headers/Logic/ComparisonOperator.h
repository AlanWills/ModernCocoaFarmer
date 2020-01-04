#pragma once

#include "Utils/ToString.h"


namespace MCF::Logic
{
  enum class ComparisonOperator
  {
    kLessThan,
    kLessThanOrEqualTo,
    kEqual,
    kGreaterThanOrEqualTo,
    kGreaterThan
  };
}

namespace CelesteEngine
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Logic::ComparisonOperator comparisonOperator);
}