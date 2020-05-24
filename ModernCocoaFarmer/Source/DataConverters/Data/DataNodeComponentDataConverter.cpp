#include "DataConverters/Data/DataNodeComponentDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/DataNodeComponent.h"
#include "Data/DataSystem.h"
#include "Data/DataUtils.h"
#include "Data/Ports/InputPort.h"
#include "Data/Ports/OutputPort.h"


namespace MCF::DataConverters::Data
{
  using namespace MCF::Data;

  //------------------------------------------------------------------------------------------------
  const char* const DataNodeComponentDataConverter::GUID_ATTRIBUTE_NAME("guid");
  const std::string OUTPUT_PORT_NAME = "OutputPort";

  //------------------------------------------------------------------------------------------------
  DataNodeComponentDataConverter::DataNodeComponentDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_guid(createReferenceAttribute<std::string>(GUID_ATTRIBUTE_NAME, "", Celeste::DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool DataNodeComponentDataConverter::DataNodeComponentDataConverter::doConvertFromXML(const XMLElement* objectElement)
  { 
    for (const tinyxml2::XMLElement* element : Celeste::XML::children(objectElement, OUTPUT_PORT_NAME))
    {
      std::unique_ptr<OutputPortDataConverter> outputPortDataConverter = std::make_unique<OutputPortDataConverter>();
      if (outputPortDataConverter->convertFromXML(element))
      {
        m_outputPortDataConverters.emplace_back(std::move(outputPortDataConverter));
      }
    }

    return true; 
  }

  //------------------------------------------------------------------------------------------------
  void DataNodeComponentDataConverter::doSetValues(Celeste::Component& component) const
  {
    doSetValues(static_cast<DataNodeComponent&>(component));
  }

  //------------------------------------------------------------------------------------------------
  void DataNodeComponentDataConverter::doSetValues(DataNodeComponent& dataNodeComponent) const
  {
    dataNodeComponent.setGuid(xg::Guid(getGuid()));

    DataSystem& dataSystem = getDataSystem();

    // Tell data system about new input ports that can potentially resolve pending connections
    for (size_t i = 0; i < dataNodeComponent.getInputPortCount(); ++i)
    {
      InputPort& port = *dataNodeComponent.getInputPort(i);
      dataSystem.addInputPort(dataNodeComponent.getGuid().str() + "::" + port.getName(), port);
    }

    for (const std::unique_ptr<OutputPortDataConverter>& outputPortDataConverter : m_outputPortDataConverters)
    {
      observer_ptr<MCF::Data::OutputPort> port = dataNodeComponent.findOutputPort(outputPortDataConverter->getPortName());
      ASSERT_NOT_NULL(port);

      if (port != nullptr)
      {
        for (const std::string& connectionName : outputPortDataConverter->getConnectionNames())
        {
          dataSystem.addPendingConnection(connectionName, *port);
        }
      }
    }
  }
}