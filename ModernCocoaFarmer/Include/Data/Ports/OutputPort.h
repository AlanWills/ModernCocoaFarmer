#pragma once

#include "Data/Utils/PortSetterFunctions.h"
#include "Persistence/Data.h"
#include "Assert/Assert.h"

#include <vector>


namespace MCF::Data
{
  class OutputPort : public Port
  {
    public:
      OutputPort(const std::string& name, size_t type) : 
        Port(name, type)
      {
      }

      void connect(InputPort& port) 
      { 
        m_connections.push_back(&port); 
      }

      template <typename T>
      void setValue(T newValue);
      
    private:
      std::vector<observer_ptr<InputPort>> m_connections;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void OutputPort::setValue(T newValue)
  {
    for (const auto& port : m_connections)
    {
      const SetterFunctions<T>& setterFunctions = getSetterFunctions<T>();

      size_t portType = port->getType();
      ASSERT(portType < setterFunctions.size());

      if (portType < setterFunctions.size())
      {
        setterFunctions.m_functions[portType](newValue, *port);
      }
    }
  }
}