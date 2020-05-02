#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Assert/Assert.h"
#include "Assert/NullAsserter.h"


namespace TestModernCocoaFarmerLibrary
{
  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestModernCocoaFarmerLibrary_Initialize)
  {
    Celeste::Assertion::setAsserter(std::make_unique<Celeste::NullAsserter>());
  }
}