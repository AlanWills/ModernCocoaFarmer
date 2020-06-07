#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::UI
{
  class ProgressBarController;
}

namespace MCF::DataConverters::Data::UI
{
  class ProgressBarControllerDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(ProgressBarControllerDataConverter, MCF::Data::UI::ProgressBarController, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}