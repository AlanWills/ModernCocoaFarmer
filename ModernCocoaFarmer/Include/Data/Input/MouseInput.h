#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"
#include "UID/StringId.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Input
{
  class MouseInput : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(MouseInput, DataSystem, MCFLibraryDllExport);

    public:
      ~MouseInput() override;

      static const std::string ON_ENTER_PORT_NAME;
      static const std::string ON_LEAVE_PORT_NAME;
      static const std::string ON_LEFT_BUTTON_UP_PORT_NAME;

      void update(const DataSystem& dataSystem) override;

    private:
      using Inherited = DataNodeComponent;

      OutputPort& m_onEnterPort;
      OutputPort& m_onLeavePort;
      OutputPort& m_onLeftButtonUpPort;

      bool m_setupComplete = false;
      Celeste::StringId m_onEnterEventHandle;
      Celeste::StringId m_onLeaveEventHandle;
      Celeste::StringId m_onLeftButtonUpEventHandle;
  };
}