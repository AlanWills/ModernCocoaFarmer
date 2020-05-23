#include "DataConverters/Data/Ports/OutputPortDataConverter.h"


namespace MCF::DataConverters::Data
{
  //------------------------------------------------------------------------------------------------
  const char* const OutputPortBaseDataConverter::CONNECTION_ELEMENT_NAME = "Connection";

  //------------------------------------------------------------------------------------------------
  OutputPortBaseDataConverter::OutputPortBaseDataConverter(const std::string& name) :
    Inherited(name),
    m_connectionNames()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool OutputPortBaseDataConverter::doConvertFromXML(const XMLElement* objectElement)
  {
    for (const tinyxml2::XMLElement* connection : Celeste::XML::children(objectElement, CONNECTION_ELEMENT_NAME))
    {
      m_connectionNames.push_back(connection->GetText());
    }

    return true;
  }
}