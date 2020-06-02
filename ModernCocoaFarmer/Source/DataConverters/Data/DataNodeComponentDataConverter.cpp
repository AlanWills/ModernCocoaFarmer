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
  const std::string INPUT_PORT_NAME = "InputPort";
  const std::string OUTPUT_PORT_NAME = "OutputPort";

  //------------------------------------------------------------------------------------------------
  DataNodeComponentDataConverter::DataNodeComponentDataConverter(const std::string& elementName) :
    Inherited(elementName)
  {
  }

  //------------------------------------------------------------------------------------------------
  bool DataNodeComponentDataConverter::DataNodeComponentDataConverter::doConvertFromXML(const XMLElement* objectElement)
  { 
    for (const tinyxml2::XMLElement* element : Celeste::XML::children(objectElement, INPUT_PORT_NAME))
    {
      std::unique_ptr<PortDataConverter> inputPortDataConverter = std::make_unique<PortDataConverter>();
      if (inputPortDataConverter->convertFromXML(element))
      {
        m_inputPortDataConverters.emplace_back(std::move(inputPortDataConverter));
      }
    }

    for (const tinyxml2::XMLElement* element : Celeste::XML::children(objectElement, OUTPUT_PORT_NAME))
    {
      std::unique_ptr<PortDataConverter> outputPortDataConverter = std::make_unique<PortDataConverter>();
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
    DataSystem& dataSystem = getDataSystem();

    for (const std::unique_ptr<PortDataConverter>& inputPortDataConverter : m_inputPortDataConverters)
    {
      observer_ptr<MCF::Data::InputPort> port = dataNodeComponent.findInputPort(inputPortDataConverter->getPortName());
      ASSERT_NOT_NULL(port);

      if (port != nullptr)
      {
        inputPortDataConverter->setValues(*port);

        for (const std::string& connectionName : inputPortDataConverter->getConnectionNames())
        {
          dataSystem.addInputPortConnection(*port, connectionName + port->getGuid().str());
        }
      }
    }

    for (const std::unique_ptr<PortDataConverter>& outputPortDataConverter : m_outputPortDataConverters)
    {
      observer_ptr<MCF::Data::OutputPort> port = dataNodeComponent.findOutputPort(outputPortDataConverter->getPortName());
      ASSERT_NOT_NULL(port);

      if (port != nullptr)
      {
        outputPortDataConverter->setValues(*port);

        for (const std::string& connectionName : outputPortDataConverter->getConnectionNames())
        {
          dataSystem.addOutputPortConnection(*port, port->getGuid().str() + connectionName);
        }
      }
    }
  }
}