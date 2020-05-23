#pragma once

#include "Objects/Component.h"
#include "Data/Ports/InputPort.h"
#include "Data/Ports/OutputPort.h"
#include "crossguid/guid.hpp"

#include <memory>
#include <vector>
#include <algorithm>


namespace MCF::Data
{
  class InputPortBase;
  class OutputPortBase;

  class DataNodeComponent : public Celeste::Component
  {
    public:
      DataNodeComponent(Celeste::GameObject& gameObject);

      virtual void OnInputPortValueChanged(const std::string& /*portName*/) {}

      const xg::Guid& getGuid() const { return m_guid; }
      void setGuid(const xg::Guid& guid) { m_guid = guid; }

      size_t getInputPortCount() const { return m_inputs.size(); }
      size_t getOutputPortCount() const { return m_outputs.size(); }

      observer_ptr<InputPortBase> getInputPort(size_t index) const;
      observer_ptr<OutputPortBase> getOutputPort(size_t index) const;

      observer_ptr<InputPortBase> findInputPort(const std::string& name) const;
      observer_ptr<OutputPortBase> findOutputPort(const std::string& name) const;

    protected:
      template <typename T>
      InputPort<T>& createInputPort(const std::string& name);

      template <typename T>
      OutputPort<T>& createOutputPort(const std::string& name);

    private:
      xg::Guid m_guid;
      std::vector<std::unique_ptr<InputPortBase>> m_inputs;
      std::vector<std::unique_ptr<OutputPortBase>> m_outputs;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  InputPort<T>& DataNodeComponent::createInputPort(const std::string& name)
  {
    ASSERT(findInputPort(name) == nullptr);
    m_inputs.emplace_back(std::make_unique<InputPort<T>>(name, *this));
    return static_cast<InputPort<T>&>(*m_inputs.back());
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  OutputPort<T>& DataNodeComponent::createOutputPort(const std::string& name)
  {
    ASSERT(findOutputPort(name) == nullptr);
    m_outputs.emplace_back(std::make_unique<OutputPort<T>>(name));
    return static_cast<OutputPort<T>&>(*m_outputs.back());
  }
}