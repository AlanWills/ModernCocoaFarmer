#include "Deserialization/Stats/ModifierEnumsDeserializers.h"


namespace CelesteEngine
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Stats::ChangeType>(const std::string& text, MCF::Stats::ChangeType& output)
  {
    if (text == "Delta")
    {
      output = MCF::Stats::ChangeType::kDelta;
      return true;
    }
    else if (text == "Absolute")
    {
      output = MCF::Stats::ChangeType::kAbsolute;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }

  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Stats::Occurrence>(const std::string& text, MCF::Stats::Occurrence& output)
  {
    if (text == "Instant")
    {
      output = MCF::Stats::Occurrence::kInstant;
      return true;
    }
    else if (text == "Periodic")
    {
      output = MCF::Stats::Occurrence::kPeriodic;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }
}