#include "DataConverters/Data/Communication/Vec3ValueForwarderDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Communication/Vec3ValueForwarder.h"
#include "Data/DataUtils.h"
#include "Data/DataSystem.h"
#include "Deserialization/MathsDeserializers.h"


namespace MCF::DataConverters::Data::Communication
{
  REGISTER_COMPONENT_DATA_CONVERTER(Vec3ValueForwarderDataConverter);

  //------------------------------------------------------------------------------------------------
  Vec3ValueForwarderDataConverter::Vec3ValueForwarderDataConverter() :
    Inherited(MCF::Data::Communication::Vec3ValueForwarder::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void Vec3ValueForwarderDataConverter::doSetValues(MCF::Data::Communication::Vec3ValueForwarder& vec3ValueForwarder) const
  {
    Inherited::doSetValues(vec3ValueForwarder);
  }
}