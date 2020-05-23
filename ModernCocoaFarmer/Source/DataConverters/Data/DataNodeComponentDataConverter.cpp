#include "DataConverters/Data/DataNodeComponentDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/DataNodeComponent.h"
#include "Data/DataSystem.h"
#include "Data/DataUtils.h"


namespace MCF::DataConverters::Data
{
  using namespace MCF::Data;

  //------------------------------------------------------------------------------------------------
  const char* const DataNodeComponentDataConverter::GUID_ATTRIBUTE_NAME("guid");

  const std::unordered_map<std::string, std::function<std::unique_ptr<InputPortBaseDataConverter>()>> s_inputPortDataConverterFactory
  {
    { "BoolInputPort", []() { return std::make_unique<InputPortDataConverter<bool>>("BoolInputPort"); } },
    { "IntInputPort", []() { return std::make_unique<InputPortDataConverter<int>>("IntInputPort"); } },
    { "UIntInputPort", []() { return std::make_unique<InputPortDataConverter<unsigned int>>("UIntInputPort"); } },
    { "FloatInputPort", []() { return std::make_unique<InputPortDataConverter<float>>("FloatInputPort"); } },
    { "StringInputPort", []() { return std::make_unique<InputPortDataConverter<std::string>>("StringInputPort"); } },
  };

  const std::unordered_map<std::string, std::function<std::unique_ptr<OutputPortBaseDataConverter>()>> s_outputPortDataConverterFactory
  {
    { "BoolOutputPort", []() { return std::make_unique<OutputPortBaseDataConverter>("BoolOutputPort"); } },
    { "IntOutputPort", []() { return std::make_unique<OutputPortBaseDataConverter>("IntOutputPort"); } },
    { "UIntOutputPort", []() { return std::make_unique<OutputPortBaseDataConverter>("UIntOutputPort"); } },
    { "FloatOutputPort", []() { return std::make_unique<OutputPortBaseDataConverter>("FloatOutputPort"); } },
    { "StringOutputPort", []() { return std::make_unique<OutputPortBaseDataConverter>("StringOutputPort"); } },
  };

  //------------------------------------------------------------------------------------------------
  DataNodeComponentDataConverter::DataNodeComponentDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_guid(createReferenceAttribute<std::string>(GUID_ATTRIBUTE_NAME, "", Celeste::DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool DataNodeComponentDataConverter::DataNodeComponentDataConverter::doConvertFromXML(const XMLElement* objectElement)
  { 
    for (const tinyxml2::XMLElement* element : Celeste::XML::children(objectElement))
    {
      if (s_inputPortDataConverterFactory.find(element->Name()) != s_inputPortDataConverterFactory.end())
      {
        // TODO CHECK CONVERT FROM XML
        m_inputPortDataConverters.emplace_back(s_inputPortDataConverterFactory.at(element->Name())());
        m_inputPortDataConverters.back()->convertFromXML(element);
      }
      else if (s_outputPortDataConverterFactory.find(element->Name()) != s_outputPortDataConverterFactory.end())
      {
        // TODO CHECK CONVERT FROM XML
        m_outputPortDataConverters.emplace_back(s_outputPortDataConverterFactory.at(element->Name())());
        m_outputPortDataConverters.back()->convertFromXML(element);
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
      InputPortBase& port = *dataNodeComponent.getInputPort(i);
      dataSystem.addInputPort(dataNodeComponent.getGuid().str() + "::" + port.getName(), port);
    }

    for (const std::unique_ptr<InputPortBaseDataConverter>& inputPortDataConverter : m_inputPortDataConverters)
    {
      observer_ptr<MCF::Data::InputPortBase> port = dataNodeComponent.findInputPort(inputPortDataConverter->getPortName());
      ASSERT_NOT_NULL(port);

      if (port != nullptr)
      {
        inputPortDataConverter->setValues(*port);
      }
    }

    for (const std::unique_ptr<OutputPortBaseDataConverter>& outputPortDataConverter : m_outputPortDataConverters)
    {
      observer_ptr<MCF::Data::OutputPortBase> port = dataNodeComponent.findOutputPort(outputPortDataConverter->getPortName());
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