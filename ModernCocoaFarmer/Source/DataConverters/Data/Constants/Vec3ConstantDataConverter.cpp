#include "DataConverters/Data/Constants/Vec3ConstantDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Constants/Vec3Constant.h"
#include "Data/DataUtils.h"
#include "Data/DataSystem.h"
#include "Deserialization/MathsDeserializers.h"


namespace MCF::DataConverters::Data::Constants
{
  REGISTER_COMPONENT_DATA_CONVERTER(Vec3ConstantDataConverter);

  //------------------------------------------------------------------------------------------------
  Vec3ConstantDataConverter::Vec3ConstantDataConverter() :
    Inherited(MCF::Data::Constants::Vec3Constant::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void Vec3ConstantDataConverter::doSetValues(MCF::Data::Constants::Vec3Constant& vec3Constant) const
  {
    Inherited::doSetValues(vec3Constant);

    vec3Constant.setValue(getValue());
    MCF::Data::getDataSystem().queueUpdate(vec3Constant);
  }
}