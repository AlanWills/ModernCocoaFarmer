#include "Data/Utils/PortSetterFunctions.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  const TypelessSetterFunctions& getSetterFunctions()
  {
    static TypelessSetterFunctions setterFunctions = celstl::createVariantFunctions<TypelessSetterFunctions, TypelessSetter>();
    return setterFunctions;
  }
}