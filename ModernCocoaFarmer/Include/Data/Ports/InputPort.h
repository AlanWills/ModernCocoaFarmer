#pragma once

#include "Data/Ports/Port.h"
#include "Data/DataNodeComponent.h"
#include "Persistence/Data.h"
#include "CelesteStl/Templates/Variant.h"


namespace MCF::Data
{
  class InputPort : public Port
  {
    public:
      InputPort(const std::string& name, size_t type, DataNodeComponent& node) :
        Port(name, type),
        m_node(node)
      {
      }

      template <typename T>
      void setValue(T value) 
      {
        m_node.OnInputPortValueChanged(getName(), value);
      }

    private:
      DataNodeComponent& m_node;
  };
}