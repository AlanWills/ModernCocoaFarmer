#include "Deserialization/Stats/ModifierEnumsDeserializers.h"


namespace Celeste
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
}