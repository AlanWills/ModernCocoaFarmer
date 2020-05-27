#include "DataConverters/Data/Conversion/ToStringDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Conversion/ToString.h"


namespace MCF::DataConverters::Data::Conversion
{
  REGISTER_COMPONENT_DATA_CONVERTER(ToStringDataConverter);

  //------------------------------------------------------------------------------------------------
  const char* const ToStringDataConverter::TYPE_ATTRIBUTE_NAME("type");

  //------------------------------------------------------------------------------------------------
  ToStringDataConverter::ToStringDataConverter() :
    Inherited(MCF::Data::Conversion::ToString::type_name()),
    m_type(createValueAttribute<size_t>(TYPE_ATTRIBUTE_NAME, size_t(), Celeste::DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ToStringDataConverter::doSetValues(MCF::Data::Conversion::ToString& toString) const
  {
    Inherited::doSetValues(toString);

    toString.setType(getType());
  }
}