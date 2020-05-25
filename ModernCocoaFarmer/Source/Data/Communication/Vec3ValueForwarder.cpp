#include "Data/Communication/Vec3ValueForwarder.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Communication
{
  REGISTER_COMPONENT(Vec3ValueForwarder, 10);

  //------------------------------------------------------------------------------------------------
  Vec3ValueForwarder::Vec3ValueForwarder(Celeste::GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}