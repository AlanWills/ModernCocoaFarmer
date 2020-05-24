#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Rendering
{
  class SpriteNode : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(SpriteNode, DataSystem, MCFLibraryDllExport)

    public:
      void OnInputPortValueChanged(const std::string& portName, const std::string& newValue) override;

      static const std::string COLOUR_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      InputPort& m_colour;
  };
}