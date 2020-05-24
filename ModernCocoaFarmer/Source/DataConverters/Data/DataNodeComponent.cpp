#include "Data/DataNodeComponent.h"
#include "Data/Ports/InputPort.h"
#include "Data/Ports/OutputPort.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  DataNodeComponent::DataNodeComponent(Celeste::GameObject& gameObject) :
    Celeste::Component(gameObject) 
  {
  }

  //------------------------------------------------------------------------------------------------
  InputPort& DataNodeComponent::createInputPort(const std::string& name, size_t type)
  {
    ASSERT(findInputPort(name) == nullptr);
    m_inputs.emplace_back(std::make_unique<InputPort>(name, type, *this));
    return static_cast<InputPort&>(*m_inputs.back());
  }

  //------------------------------------------------------------------------------------------------
  OutputPort& DataNodeComponent::createOutputPort(const std::string& name, size_t type)
  {
    ASSERT(findOutputPort(name) == nullptr);
    m_outputs.emplace_back(std::make_unique<OutputPort>(name, type));
    return static_cast<OutputPort&>(*m_outputs.back());
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<InputPort> DataNodeComponent::getInputPort(size_t index) const
  {
    ASSERT(index < m_inputs.size());
    return index < m_inputs.size() ? m_inputs[index].get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<OutputPort> DataNodeComponent::getOutputPort(size_t index) const
  {
    ASSERT(index < m_outputs.size());
    return index < m_outputs.size() ? m_outputs[index].get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<InputPort> DataNodeComponent::findInputPort(const std::string& name) const
  {
    auto inputIt = std::find_if(m_inputs.begin(), m_inputs.end(),
      [&name](const std::unique_ptr<InputPort>& port)
      {
        return port->getName() == name;
      });

    return inputIt != m_inputs.end() ? inputIt->get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<OutputPort> DataNodeComponent::findOutputPort(const std::string& name) const
  {
    auto outputIt = std::find_if(m_outputs.begin(), m_outputs.end(),
      [&name](const std::unique_ptr<OutputPort>& port)
      {
        return port->getName() == name;
      });

    return outputIt != m_outputs.end() ? outputIt->get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void DataNodeComponent::removeInputPort(const std::string& name)
  {
    auto inputIt = std::find_if(m_inputs.begin(), m_inputs.end(),
      [&name](const std::unique_ptr<InputPort>& port)
      {
        return port->getName() == name;
      });

    if (inputIt != m_inputs.end())
    {
      m_inputs.erase(inputIt);
    }
  }

  //------------------------------------------------------------------------------------------------
  void DataNodeComponent::removeOutputPort(const std::string& name)
  {
    auto outputIt = std::find_if(m_outputs.begin(), m_outputs.end(),
      [&name](const std::unique_ptr<OutputPort>& port)
      {
        return port->getName() == name;
      });

    if (outputIt != m_outputs.end())
    {
      m_outputs.erase(outputIt);
    }
  }
}