#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::Data::Animation
{
  class AnimatorController;
}

namespace MCF::DataConverters::Data::Animation
{
  class AnimatorControllerDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(AnimatorControllerDataConverter, MCF::Data::Animation::AnimatorController, MCFLibraryDllExport);

    private:
      using Inherited = DataNodeComponentDataConverter;
  };
}