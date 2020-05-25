#include "DataConverters/Data/Rendering/SpriteDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Rendering/Sprite.h"


namespace MCF::DataConverters::Data::Rendering
{
  REGISTER_COMPONENT_DATA_CONVERTER(SpriteDataConverter);

  //------------------------------------------------------------------------------------------------
  SpriteDataConverter::SpriteDataConverter() :
    Inherited(MCF::Data::Rendering::Sprite::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void SpriteDataConverter::doSetValues(MCF::Data::Rendering::Sprite& spriteNode) const
  {
    Inherited::doSetValues(spriteNode);
  }
}