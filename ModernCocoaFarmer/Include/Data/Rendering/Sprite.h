#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Rendering
{
  class Sprite : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(Sprite, DataSystem, MCFLibraryDllExport)

    public:
      static const std::string COLOUR_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onColourChanged(const NewValue& newValue);

      InputPort& m_colour;
  };
}