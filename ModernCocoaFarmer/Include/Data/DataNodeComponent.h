#pragma once

#include "Objects/Component.h"
#include "CelesteStl/Templates/Variant.h"
#include "Persistence/Data.h"
#include "crossguid/guid.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <algorithm>


namespace MCF::Data
{
  class InputPort;
  class OutputPort;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  constexpr size_t type()
  {
    return celstl::variant_index<Persistence::Data, T>();
  }

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

      virtual void OnInputPortValueChanged(const std::string& /*portName*/, bool /*newValue*/) {}
      virtual void OnInputPortValueChanged(const std::string& /*portName*/, int /*newValue*/) {}
      virtual void OnInputPortValueChanged(const std::string& /*portName*/, unsigned int /*newValue*/) {}
      virtual void OnInputPortValueChanged(const std::string& /*portName*/, float /*newValue*/) {}
      virtual void OnInputPortValueChanged(const std::string& /*portName*/, const std::string& /*newValue*/) {}
      virtual void OnInputPortValueChanged(const std::string& /*portName*/, const glm::vec3& /*newValue*/) {}

    protected:
      InputPort& createInputPort(const std::string& name, size_t type);
      OutputPort& createOutputPort(const std::string& name, size_t type);

    private:
      xg::Guid m_guid;
      std::vector<std::unique_ptr<InputPort>> m_inputs;
      std::vector<std::unique_ptr<OutputPort>> m_outputs;
  };
}