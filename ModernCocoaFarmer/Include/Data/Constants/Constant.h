#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Constants
{
  class Constant : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(Constant, DataSystem, MCFLibraryDllExport);

    public:
      template <typename T>
      void setValue(T newValue);
      void setValue(const Persistence::Data& newValue);

      void update(float elapsedGameTime) override;

      static const std::string VALUE_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      OutputPort& m_valuePort;
      Persistence::Data m_value;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void Constant::setValue(T newValue)
  {
    m_value = newValue;
    m_valuePort.setType(PortType<T>::value());
    m_valuePort.setValue(newValue);
  }
}