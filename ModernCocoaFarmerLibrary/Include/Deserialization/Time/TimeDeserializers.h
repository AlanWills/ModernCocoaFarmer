#pragma once

#include "Deserialization/Deserializers.h"
#include "Time/TimePeriod.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Time::TimePeriod>(const std::string& text, MCF::Time::TimePeriod& output);
}