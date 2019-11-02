#pragma once

#include "Deserialization/Deserializers.h"
#include "Stats/ModifierEnums.h"


namespace CelesteEngine
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Stats::ChangeType>(const std::string& text, MCF::Stats::ChangeType& output);

  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Stats::Occurrence>(const std::string& text, MCF::Stats::Occurrence& output);
}