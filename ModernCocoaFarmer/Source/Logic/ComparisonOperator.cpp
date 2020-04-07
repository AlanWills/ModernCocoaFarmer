#include "Logic/ComparisonOperator.h"
#include "Assert/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Logic::ComparisonOperator comparisonOperator)
  {
    using namespace MCF::Logic;

    switch (comparisonOperator)
    {
    case ComparisonOperator::kLessThan:
      return "LessThan";

    case ComparisonOperator::kLessThanOrEqualTo:
      return "LessThanOrEqualTo";

    case ComparisonOperator::kEqual:
      return "Equals";

    case ComparisonOperator::kGreaterThanOrEqualTo:
      return "GreaterThanOrEqualTo";

    case ComparisonOperator::kGreaterThan:
      return "GreaterThan";

    default:
      ASSERT_FAIL();
      return "";
    }
  }
}