#pragma once

#include "Data/Ports/Port.h"
#include "Persistence/Data.h"
#include "CelesteStl/Templates/Variant.h"


namespace MCF::Data
{
  class DataNodeComponent;

  class InputPortBase : public Port
  {
    public:
      InputPortBase(const std::string& name, DataNodeComponent& node) :
        Port(name),
        m_node(node)
      {
      }

    protected:
      DataNodeComponent& getNode() { return m_node; }

      void notifyNodeOnValueChange();

    private:
      DataNodeComponent& m_node;
  };

  template <typename T>
  class InputPort : public InputPortBase
  {
    public:
      InputPort(const std::string& name, DataNodeComponent& node) :
        InputPortBase(name, node)
      {
      }
      
      size_t getType() const override { return celstl::variant_index<Persistence::Data, T>(); }
      const T& getValue() const { return m_value; }
      
      void setValue(T value) 
      { 
        m_value = value;
        notifyNodeOnValueChange();
      }

    private:
      T m_value;
  };

  //------------------------------------------------------------------------------------------------
  using BoolInputPort = InputPort<bool>;
  using IntInputPort = InputPort<int>;
  using UIntInputPort = InputPort<unsigned int>;
  using FloatInputPort = InputPort<float>;
  using StringInputPort = InputPort<std::string>;
}