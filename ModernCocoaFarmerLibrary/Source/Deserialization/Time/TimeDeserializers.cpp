#include "Deserialization/Time/TimeDeserializers.h"


namespace CelesteEngine
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Time::TimePeriod>(const std::string& text, MCF::Time::TimePeriod& output)
  {
    if (text == "day" || text == "Day")
    {
      output = MCF::Time::TimePeriod::kDay;
      return true;
    }
    else if (text == "month" || text == "Month")
    {
      output = MCF::Time::TimePeriod::kMonth;
      return true;
    }
    else if (text == "year" || text == "Year")
    {
      output = MCF::Time::TimePeriod::kYear;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }
}