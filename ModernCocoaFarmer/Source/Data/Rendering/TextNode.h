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
      void OnInputPortValueChanged(const std::string& portName) override;

    private:
      using Inherited = DataNodeComponent;

      StringInputPort& m_text;
  };
}