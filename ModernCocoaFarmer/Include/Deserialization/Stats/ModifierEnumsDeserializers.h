#pragma once

#include "Deserialization/Deserializers.h"
#include "Stats/ModifierEnums.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Stats::ChangeType>(const std::string& text, MCF::Stats::ChangeType& output);
}