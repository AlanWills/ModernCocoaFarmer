#include "DataConverters/Data/Communication/DataObjectKeyDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Communication/DataObjectKey.h"


namespace MCF::DataConverters::Data::Communication
{
  REGISTER_COMPONENT_DATA_CONVERTER(DataObjectKeyDataConverter);

  //------------------------------------------------------------------------------------------------
  DataObjectKeyDataConverter::DataObjectKeyDataConverter() :
    Inherited(MCF::Data::Communication::DataObjectKey::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void DataObjectKeyDataConverter::doSetValues(MCF::Data::Communication::DataObjectKey& dataObjectKey) const
  {
    // Create the output ports first before calling the base class which will set the values up
    for (const auto& outputPortDataConverter : getOutputPortDataConverters())
    {
      dataObjectKey.addSubKey(outputPortDataConverter->getPortName());
    }

    Inherited::doSetValues(dataObjectKey);
  }
}