#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Rendering
{
  class Text : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(Text, DataSystem, MCFLibraryDllExport);

    public:
      static const std::string TEXT_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;
      
      void onTextChanged(Persistence::Data&& newValue);

      InputPort& m_text;
  };
}