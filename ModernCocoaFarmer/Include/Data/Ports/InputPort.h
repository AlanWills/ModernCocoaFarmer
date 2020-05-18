#pragma once

#include "Data/Ports/Port.h"
#include "Persistence/Data.h"
#include "CelesteStl/Templates/Variant.h"


namespace MCF::Data
{
  template <typename T>
  class InputPort : public Port
  {
    public:
      InputPort(const std::string& name) :
        Port(name)
      {
      }
      
      size_t getType() const override { return celstl::variant_index<Persistence::Data, T>(); }
      
      const T& getValue() const { return m_value; }
      void setValue(T value) { m_value = value; }

    private:
      T m_value;
      //DataNode m_node;  // Next step is to notify owner that value has changed
  };
}