#include "DataConverters/Data/Maths/DivisionDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Maths/Division.h"


namespace MCF::DataConverters::Data::Maths
{
  REGISTER_COMPONENT_DATA_CONVERTER(DivisionDataConverter);

  //------------------------------------------------------------------------------------------------
  DivisionDataConverter::DivisionDataConverter() :
    Inherited(MCF::Data::Maths::Division::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void DivisionDataConverter::doSetValues(MCF::Data::Maths::Division& division) const
  {
    Inherited::doSetValues(division);
  }
}