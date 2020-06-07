#include "DataConverters/Data/Input/MouseInputDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Input/MouseInput.h"
#include "Data/DataSystem.h"
#include "Data/DataUtils.h"


namespace MCF::DataConverters::Data::Input
{
  REGISTER_COMPONENT_DATA_CONVERTER(MouseInputDataConverter);

  //------------------------------------------------------------------------------------------------
  MouseInputDataConverter::MouseInputDataConverter() :
    Inherited(MCF::Data::Input::MouseInput::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void MouseInputDataConverter::doSetValues(MCF::Data::Input::MouseInput& mouseInput) const
  {
    Inherited::doSetValues(mouseInput);

    MCF::Data::getDataSystem().queueUpdate(mouseInput);
  }
}