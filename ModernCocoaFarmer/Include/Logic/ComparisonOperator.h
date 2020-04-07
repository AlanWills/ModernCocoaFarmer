#pragma once

#include "Utils/ToString.h"
#include "Assert/Assert.h"


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

  template <typename T>
  bool isComparisonTrue(const T& actual, const T& expected, ComparisonOperator comparisonOperator);
}

namespace MCF::Logic
{
  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool isComparisonTrue(const T& actual, const T& expected, ComparisonOperator comparisonOperator)
  {
    switch (comparisonOperator)
    {
    case ComparisonOperator::kLessThan:
      return actual < expected;

    case ComparisonOperator::kLessThanOrEqualTo:
      return actual <= expected;

    case ComparisonOperator::kEqual:
      return actual == expected;

    case ComparisonOperator::kGreaterThanOrEqualTo:
      return actual >= expected;

    case ComparisonOperator::kGreaterThan:
      return actual > expected;

    default:
      ASSERT_FAIL();
      return false;
    }
  }
}

namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Logic::ComparisonOperator comparisonOperator);
}