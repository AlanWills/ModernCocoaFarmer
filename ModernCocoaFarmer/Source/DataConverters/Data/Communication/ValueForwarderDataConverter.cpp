#include "DataConverters/Data/Communication/ValueForwarderDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Communication/ValueForwarder.h"
#include "Data/DataUtils.h"
#include "Data/DataSystem.h"


namespace MCF::DataConverters::Data::Communication
{
  REGISTER_COMPONENT_DATA_CONVERTER(ValueForwarderDataConverter);

  //------------------------------------------------------------------------------------------------
  const char* const ValueForwarderDataConverter::TYPE_ATTRIBUTE_NAME("type");

  //------------------------------------------------------------------------------------------------
  ValueForwarderDataConverter::ValueForwarderDataConverter() :
    Inherited(MCF::Data::Communication::ValueForwarder::type_name()),
    m_type(createValueAttribute<size_t>(TYPE_ATTRIBUTE_NAME, size_t(), Celeste::DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ValueForwarderDataConverter::doSetValues(MCF::Data::Communication::ValueForwarder& valueForwarder) const
  {
    Inherited::doSetValues(valueForwarder);

    valueForwarder.setType(getType());
  }
}