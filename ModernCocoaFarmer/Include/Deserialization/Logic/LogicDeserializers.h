#pragma once

#include "Deserialization/Deserializers.h"
#include "Logic/ComparisonOperator.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<MCF::Logic::ComparisonOperator>(const std::string& text, MCF::Logic::ComparisonOperator& output);
}