#include "DataConverters/Data/Communication/DataReaderDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Communication/DataReader.h"


namespace MCF::DataConverters::Data::Communication
{
  REGISTER_COMPONENT_DATA_CONVERTER(DataReaderDataConverter);

  //------------------------------------------------------------------------------------------------
  const char* const DataReaderDataConverter::TYPE_ATTRIBUTE_NAME = "type";
  const char* const DataReaderDataConverter::KEY_ATTRIBUTE_NAME = "key";

  //------------------------------------------------------------------------------------------------
  DataReaderDataConverter::DataReaderDataConverter() :
    Inherited(MCF::Data::Communication::DataReader::type_name()),
    m_type(createValueAttribute<size_t>(TYPE_ATTRIBUTE_NAME, MCF::Data::type<bool>(), Celeste::DeserializationRequirement::kRequired)),
    m_key(createReferenceAttribute<std::string>(KEY_ATTRIBUTE_NAME, "", Celeste::DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  void DataReaderDataConverter::doSetValues(MCF::Data::Communication::DataReader& dataReader) const
  {
    Inherited::doSetValues(dataReader);

    dataReader.setType(getType());
    dataReader.setKey(getKey());
  }
}