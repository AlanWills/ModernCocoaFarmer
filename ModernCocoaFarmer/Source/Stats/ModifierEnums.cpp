#include "Stats/ModifierEnums.h"
#include "Assert/Assert.h"


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
}