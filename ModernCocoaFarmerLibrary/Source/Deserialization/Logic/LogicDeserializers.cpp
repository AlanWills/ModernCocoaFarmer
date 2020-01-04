#include "Deserialization/Logic/LogicDeserializers.h"


namespace CelesteEngine
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Logic::ComparisonOperator>(const std::string& text, MCF::Logic::ComparisonOperator& output)
  {
    using namespace MCF::Logic;

    if (text == "LessThan")
    {
      output = ComparisonOperator::kLessThan;
      return true;
    }
    else if (text == "LessThanOrEqualTo")
    {
      output = ComparisonOperator::kLessThanOrEqualTo;
      return true;
    }
    else if (text == "Equals")
    {
      output = ComparisonOperator::kEqual;
      return true;
    }
    else if (text == "GreaterThanOrEqualTo")
    {
      output = ComparisonOperator::kGreaterThanOrEqualTo;
      return true;
    }
    else if (text == "GreaterThan")
    {
      output = ComparisonOperator::kGreaterThan;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }
}