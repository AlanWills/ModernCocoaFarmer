#include "DataConverters/Data/UI/ProgressBarControllerDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/UI/ProgressBarController.h"


namespace MCF::DataConverters::Data::UI
{
  REGISTER_COMPONENT_DATA_CONVERTER(ProgressBarControllerDataConverter);

  //------------------------------------------------------------------------------------------------
  ProgressBarControllerDataConverter::ProgressBarControllerDataConverter() :
    Inherited(MCF::Data::UI::ProgressBarController::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void ProgressBarControllerDataConverter::doSetValues(MCF::Data::UI::ProgressBarController& progressBarController) const
  {
    Inherited::doSetValues(progressBarController);
  }
}