#include "DataConverters/Data/Logic/NotDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Logic/Not.h"


namespace MCF::DataConverters::Data::Logic
{
  REGISTER_COMPONENT_DATA_CONVERTER(NotDataConverter);

  //------------------------------------------------------------------------------------------------
  NotDataConverter::NotDataConverter() :
    Inherited(MCF::Data::Logic::Not::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void NotDataConverter::doSetValues(MCF::Data::Logic::Not& notNode) const
  {
    Inherited::doSetValues(notNode);
  }
}