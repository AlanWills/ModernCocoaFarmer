#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  DataNodeComponent::DataNodeComponent(Celeste::GameObject& gameObject) :
    Celeste::Component(gameObject) 
  {
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