#include "DataConverters/Data/Ports/PortDataConverter.h"
#include "Data/Ports/Port.h"


namespace MCF::DataConverters::Data
{
  //------------------------------------------------------------------------------------------------
  const char* const PortDataConverter::PORT_NAME_ATTRIBUTE_NAME = "name";
  const char* const PortDataConverter::GUID_ATTRIBUTE_NAME("guid");
  const char* const PortDataConverter::CONNECTION_ELEMENT_NAME = "Connection";

  //------------------------------------------------------------------------------------------------
  PortDataConverter::PortDataConverter() :
    Inherited("OutputPort"),
    m_portName(createReferenceAttribute<std::string>(PORT_NAME_ATTRIBUTE_NAME, "", Celeste::DeserializationRequirement::kRequired)),
    m_guid(createReferenceAttribute<std::string>(GUID_ATTRIBUTE_NAME, "", Celeste::DeserializationRequirement::kRequired)),
    m_connectionNames()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool PortDataConverter::doConvertFromXML(const XMLElement* objectElement)
  {
    for (const tinyxml2::XMLElement* connection : Celeste::XML::children(objectElement, CONNECTION_ELEMENT_NAME))
    {
      m_connectionNames.push_back(connection->GetText());
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  void PortDataConverter::setValues(MCF::Data::Port& port) const
  {
    port.setGuid(xg::Guid(getGuid()));
  }
}