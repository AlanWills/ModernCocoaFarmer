#include "Data/Ports/OutputPort.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  OutputPort::OutputPort(const std::string& name, size_t type) :
    Inherited(name, type)
  {
  }

  //------------------------------------------------------------------------------------------------
  void OutputPort::connect(InputPort& port)
  {
    m_connections.push_back(&port);
  }

  //------------------------------------------------------------------------------------------------
  void OutputPort::setValue(const Persistence::Data& data)
  {
    for (const auto& port : m_connections)
    {
      const auto& setterFunctions = getSetterFunctions();
      ASSERT(data.index() < setterFunctions.size());

      if (data.index() < setterFunctions.size())
      {
        setterFunctions.m_functions[data.index()](data, *port);
      }
    }
  }
}