#include "DataConverters/Data/Ports/OutputPortDataConverter.h"


namespace MCF::DataConverters::Data
{
  //------------------------------------------------------------------------------------------------
  const char* const OutputPortDataConverter::PORT_NAME_ATTRIBUTE_NAME = "name";
  const char* const OutputPortDataConverter::CONNECTION_ELEMENT_NAME = "Connection";

  //------------------------------------------------------------------------------------------------
  OutputPortDataConverter::OutputPortDataConverter() :
    Inherited("OutputPort"),
    m_portName(createReferenceAttribute<std::string>(PORT_NAME_ATTRIBUTE_NAME, "", Celeste::DeserializationRequirement::kRequired)),
    m_connectionNames()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool OutputPortDataConverter::doConvertFromXML(const XMLElement* objectElement)
  {
    for (const tinyxml2::XMLElement* connection : Celeste::XML::children(objectElement, CONNECTION_ELEMENT_NAME))
    {
      m_connectionNames.push_back(connection->GetText());
    }

    return true;
  }
}