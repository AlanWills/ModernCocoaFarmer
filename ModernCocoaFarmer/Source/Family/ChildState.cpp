#include "Family/ChildState.h"
#include "Assert/Assert.h"

using namespace MCF::Family;


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(ChildState childState)
  {
    switch (childState)
    {
    case ChildState::kNotBorn:
      return "NotBorn";

    case ChildState::kActive:
      return "Active";

    case ChildState::kGraduated:
      return "Graduated";

    case ChildState::kDead:
      return "Dead";

    default:
      ASSERT_FAIL();
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool from_string(const std::string& string, ChildState& childState)
  {
    if (string == "NotBorn")
    {
      childState = ChildState::kNotBorn;
      return true;
    }
    else if (string == "Active")
    {
      childState = ChildState::kActive;
      return true;
    }
    else if (string == "Graduated")
    {
      childState = ChildState::kGraduated;
      return true;
    }
    else if (string == "Dead")
    {
      childState = ChildState::kDead;
      return true;
    }

    return false;
  }
}