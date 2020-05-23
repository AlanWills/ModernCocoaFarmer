#pragma once

#include "Data/Utils/PortSetterFunctions.h"
#include "Persistence/Data.h"
#include "Assert/Assert.h"

#include <vector>


namespace MCF::Data
{
  class OutputPortBase : public Port
  {
    public:
      OutputPortBase(const std::string& name) : Port(name) {}

      void connect(InputPortBase& port) { m_connections.push_back(&port); }

    protected:
      const std::vector<observer_ptr<InputPortBase>>& getConnections() const { return m_connections; }

    private:
      std::vector<observer_ptr<InputPortBase>> m_connections;
  };

  template <typename T>
  class OutputPort : public OutputPortBase
  {
    public:
      OutputPort(const std::string& name);

      size_t getType() const override { return celstl::variant_index<Persistence::Data, T>(); }
      void setValue(T newValue);

    private:
      using Inherited = OutputPortBase;
      using SetterFunctions = MCF::Data::SetterFunctions<Persistence::Data, void, T, InputPortBase&>;

      static SetterFunctions m_setterFunctions;
  };

  //------------------------------------------------------------------------------------------------
  using BoolOutputPort = OutputPort<bool>;
  using IntOutputPort = OutputPort<int>;
  using UIntOutputPort = OutputPort<unsigned int>;
  using FloatOutputPort = OutputPort<float>;
  using StringOutputPort = OutputPort<std::string>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  typename OutputPort<T>::SetterFunctions OutputPort<T>::m_setterFunctions = createSetterFunctions<typename OutputPort<T>::SetterFunctions, T, Setter>();

  //------------------------------------------------------------------------------------------------
  template <typename T>
  OutputPort<T>::OutputPort(const std::string& name)
    : OutputPortBase(name)
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void OutputPort<T>::setValue(T newValue)
  {
    for (const auto& port : getConnections())
    {
      size_t portType = port->getType();
      ASSERT(portType < m_setterFunctions.size());

      if (portType < m_setterFunctions.size())
      {
        m_setterFunctions.m_functions[portType](newValue, *port);
      }
    }
  }
}