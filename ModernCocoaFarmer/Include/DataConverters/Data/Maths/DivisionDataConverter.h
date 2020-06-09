#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Maths
{
  class Division;
}

namespace MCF::DataConverters::Data::Maths
{
  class DivisionDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(DivisionDataConverter, MCF::Data::Maths::Division, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}