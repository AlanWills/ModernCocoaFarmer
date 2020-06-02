#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Objects
{
  class ActivityController;
}

namespace MCF::DataConverters::Data::Objects
{
  class ActivityControllerDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(ActivityControllerDataConverter, MCF::Data::Objects::ActivityController, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}