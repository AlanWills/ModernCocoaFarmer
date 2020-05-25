#include "DataConverters/Data/Rendering/TextDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Rendering/Text.h"


namespace MCF::DataConverters::Data::Rendering
{
  REGISTER_COMPONENT_DATA_CONVERTER(TextDataConverter);

  //------------------------------------------------------------------------------------------------
  TextDataConverter::TextDataConverter() :
    Inherited(MCF::Data::Rendering::Text::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void TextDataConverter::doSetValues(MCF::Data::Rendering::Text& textNode) const
  {
    Inherited::doSetValues(textNode);
  }
}