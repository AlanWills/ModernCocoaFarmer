#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Communication
{
  class ValueForwarder : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(ValueForwarder, DataSystem, MCFLibraryDllExport);

    public:
      size_t getType() const { return m_valuePort.getType(); }
      void setType(size_t type) { m_valuePort.setType(type); }

      static const std::string VALUE_PORT_NAME;
      static const std::string TRIGGER_PORT_NAME;
      static const std::string OUTPUT_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onValuePortChanged(Persistence::Data&& newValue);
      void onTriggerPortChanged(Persistence::Data&& newValue);

      InputPort& m_valuePort;
      InputPort& m_triggerPort;
      OutputPort& m_outputPort;

      Persistence::Data m_value;
  };
}