#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Rendering
{
  class TextNode : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(TextNode, DataSystem, MCFLibraryDllExport);

    public:
      void onTextChanged(const NewValue& newValue);

      static const std::string TEXT_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      InputPort& m_text;
  };
}