#include "DataConverters/Data/Ports/PortDataConverter.h"


namespace MCF::DataConverters::Data
{
  const char* const PortDataConverter::PORT_NAME_ATTRIBUTE_NAME = "name";

  //------------------------------------------------------------------------------------------------
  PortDataConverter::PortDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_portName(createReferenceAttribute<std::string>(PORT_NAME_ATTRIBUTE_NAME))
  {
  }
}