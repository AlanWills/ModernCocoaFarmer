#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Objects
{
  class ActivityController : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(ActivityController, DataSystem, MCFLibraryDllExport);

    public:
      static const std::string IS_ACTIVE_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onIsActivePortChanged(Persistence::Data&& newValue);

      InputPort& m_isActivePort;
  };
}