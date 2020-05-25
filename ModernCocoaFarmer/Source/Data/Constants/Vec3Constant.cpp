#include "Data/Constants/Vec3Constant.h"
#include "UtilityHeaders/ComponentHeaders.h"  


namespace MCF::Data::Constants
{
  REGISTER_COMPONENT(Vec3Constant, 10);

  //------------------------------------------------------------------------------------------------
  Vec3Constant::Vec3Constant(Celeste::GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}