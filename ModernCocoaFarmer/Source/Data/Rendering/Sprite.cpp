#include "Data/Rendering/Sprite.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Rendering/SpriteRenderer.h"


namespace MCF::Data::Rendering
{
  REGISTER_COMPONENT(Sprite, 20);

  //------------------------------------------------------------------------------------------------
  const std::string Sprite::COLOUR_PORT_NAME("colour");

  //------------------------------------------------------------------------------------------------
  Sprite::Sprite(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_colour(createInputPort<glm::vec3>(COLOUR_PORT_NAME, [this](const NewValue& newValue) { onColourChanged(newValue); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  void Sprite::onColourChanged(const NewValue& newValue)
  {
    Celeste::Rendering::SpriteRenderer* renderer = getGameObject()->findComponent<Celeste::Rendering::SpriteRenderer>();
    ASSERT_NOT_NULL(renderer);

    if (renderer != nullptr)
    {
      renderer->setColour(newValue.get<glm::vec3>());
    }
  }
}