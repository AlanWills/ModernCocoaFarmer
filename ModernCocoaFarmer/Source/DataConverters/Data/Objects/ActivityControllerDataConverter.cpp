#include "DataConverters/Data/Objects/ActivityControllerDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Objects/ActivityController.h"


namespace MCF::DataConverters::Data::Objects
{
  REGISTER_COMPONENT_DATA_CONVERTER(ActivityControllerDataConverter);

  //------------------------------------------------------------------------------------------------
  ActivityControllerDataConverter::ActivityControllerDataConverter() :
    Inherited(MCF::Data::Objects::ActivityController::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void ActivityControllerDataConverter::doSetValues(MCF::Data::Objects::ActivityController& activityController) const
  {
    Inherited::doSetValues(activityController);
  }
}