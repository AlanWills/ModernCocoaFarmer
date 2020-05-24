#pragma once

#include "Objects/Component.h"
#include "CelesteStl/Templates/Variant.h"
#include "Persistence/Data.h"
#include "crossguid/guid.hpp"
#include "Data/Ports/InputPort.h"
#include "Data/Ports/OutputPort.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <algorithm>


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct PortType
  {
    using type = T;

    static constexpr size_t value() { return celstl::variant_index<Persistence::Data, T>(); }
  };

  //------------------------------------------------------------------------------------------------
  class DataNodeComponent : public Celeste::Component
  {
    public:
      DataNodeComponent(Celeste::GameObject& gameObject);

      const xg::Guid& getGuid() const { return m_guid; }
      void setGuid(const xg::Guid& guid) { m_guid = guid; }

      size_t getInputPortCount() const { return m_inputs.size(); }
      size_t getOutputPortCount() const { return m_outputs.size(); }

      observer_ptr<InputPort> getInputPort(size_t index) const;
      observer_ptr<OutputPort> getOutputPort(size_t index) const;

      observer_ptr<InputPort> findInputPort(const std::string& name) const;
      observer_ptr<OutputPort> findOutputPort(const std::string& name) const;

      void removeInputPort(const std::string& name);
      void removeOutputPort(const std::string& name);

    protected:
      template <typename T>
      InputPort& createInputPort(const std::string& name, InputPort::ValueChangedCallback valueChanged);

      template <typename T>
      OutputPort& createOutputPort(const std::string& name);

    private:
      xg::Guid m_guid;
      std::vector<std::unique_ptr<InputPort>> m_inputs;
      std::vector<std::unique_ptr<OutputPort>> m_outputs;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  InputPort& DataNodeComponent::createInputPort(const std::string& name, InputPort::ValueChangedCallback valueChanged)
  {
    ASSERT(findInputPort(name) == nullptr);
    m_inputs.emplace_back(std::make_unique<InputPort>(name, PortType<T>::value(), valueChanged));
    return static_cast<InputPort&>(*m_inputs.back());
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  OutputPort& DataNodeComponent::createOutputPort(const std::string& name)
  {
    ASSERT(findOutputPort(name) == nullptr);
    m_outputs.emplace_back(std::make_unique<OutputPort>(name, PortType<T>::value()));
    return static_cast<OutputPort&>(*m_outputs.back());
  }
}