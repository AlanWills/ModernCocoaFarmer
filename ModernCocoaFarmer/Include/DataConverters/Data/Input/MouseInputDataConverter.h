#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Input
{
  class MouseInput;
}

namespace MCF::DataConverters::Data::Input
{
  class MouseInputDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(MouseInputDataConverter, MCF::Data::Input::MouseInput, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}