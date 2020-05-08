#pragma once

#include "Utils/ToString.h"


namespace MCF::Family
{
  enum class ChildState
  {
    kNotBorn,
    kActive,
    kGraduated,
    kDead
  };
}

namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(MCF::Family::ChildState childState);

  //------------------------------------------------------------------------------------------------
  template <>
  bool from_string(const std::string& string, MCF::Family::ChildState& childState);
}