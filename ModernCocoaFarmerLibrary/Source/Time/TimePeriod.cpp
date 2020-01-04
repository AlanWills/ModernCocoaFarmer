#include "Time/TimePeriod.h"
#include "Debug/Assert.h"


namespace CelesteEngine
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Time::TimePeriod timePeriod)
  {
    using namespace MCF::Time;

    switch (timePeriod)
    {
    case TimePeriod::kDay:
      return "day";
      
    case TimePeriod::kMonth:
      return "month";

    case TimePeriod::kYear:
      return "year";

    default:
      ASSERT_FAIL();
      return "";
    }
  }
}