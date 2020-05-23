#include "DataConverters/Data/Communication/StringDataReaderDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Communication/DataReader.h"


namespace MCF::DataConverters::Data::Communication
{
  REGISTER_COMPONENT_DATA_CONVERTER(StringDataReaderDataConverter);

  //------------------------------------------------------------------------------------------------
  StringDataReaderDataConverter::StringDataReaderDataConverter() :
    Inherited(MCF::Data::Communication::StringDataReader::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void StringDataReaderDataConverter::doSetValues(MCF::Data::Communication::StringDataReader& dataReader) const
  {
    Inherited::doSetValues(dataReader);
  }
}