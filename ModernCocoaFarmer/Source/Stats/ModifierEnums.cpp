#include "Stats/ModifierEnums.h"
#include "Debug/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Stats::ChangeType changeType)
  {
    if (changeType == MCF::Stats::ChangeType::kAbsolute)
    {
      return "Absolute";
    }
    else if (changeType == MCF::Stats::ChangeType::kDelta)
    {
      return "Delta";
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Stats::Occurrence occurrence)
  {
    if (occurrence == MCF::Stats::Occurrence::kInstant)
    {
      return "Instant";
    }
    else if (occurrence == MCF::Stats::Occurrence::kPeriodic)
    {
      return "Periodic";
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }
}