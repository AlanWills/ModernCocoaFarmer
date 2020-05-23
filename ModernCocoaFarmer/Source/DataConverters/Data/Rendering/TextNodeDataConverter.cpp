#include "DataConverters/Data/Rendering/TextNodeDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Rendering/TextNode.h"


namespace MCF::DataConverters::Data::Rendering
{
  REGISTER_COMPONENT_DATA_CONVERTER(TextNodeDataConverter);

  //------------------------------------------------------------------------------------------------
  TextNodeDataConverter::TextNodeDataConverter() :
    Inherited(MCF::Data::Rendering::TextNode::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void TextNodeDataConverter::doSetValues(MCF::Data::Rendering::TextNode& textNode) const
  {
    Inherited::doSetValues(textNode);
  }
}