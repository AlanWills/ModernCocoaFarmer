#include "DataConverters/Data/Animation/AnimatorControllerDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Animation/AnimatorController.h"


namespace MCF::DataConverters::Data::Animation
{
  REGISTER_COMPONENT_DATA_CONVERTER(AnimatorControllerDataConverter);

  //------------------------------------------------------------------------------------------------
  AnimatorControllerDataConverter::AnimatorControllerDataConverter() :
    Inherited(MCF::Data::Animation::AnimatorController::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void AnimatorControllerDataConverter::doSetValues(MCF::Data::Animation::AnimatorController& animatorController) const
  {
    Inherited::doSetValues(animatorController);
  }
}