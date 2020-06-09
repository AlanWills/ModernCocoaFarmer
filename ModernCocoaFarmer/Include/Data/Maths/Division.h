#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Maths
{
  class Division : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(Division, DataSystem, MCFLibraryDllExport);

    public:
      static const std::string X_PORT_NAME;
      static const std::string Y_PORT_NAME;
      static const std::string VALUE_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onXPortChanged(Persistence::Data&& newValue);
      void onYPortChanged(Persistence::Data&& newValue);

      InputPort& m_xPort;
      InputPort& m_yPort;
      OutputPort& m_valuePort;

      float m_x = 0;
      float m_y = 1;
  };
}