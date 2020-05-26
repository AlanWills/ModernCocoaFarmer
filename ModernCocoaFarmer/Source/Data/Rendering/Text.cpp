#include "Data/Rendering/Text.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Objects/GameObject.h"
#include "Rendering/TextRenderer.h"


namespace MCF::Data::Rendering
{
  REGISTER_COMPONENT(Text, 30);

  //------------------------------------------------------------------------------------------------
  const std::string Text::TEXT_PORT_NAME = "text";

  //------------------------------------------------------------------------------------------------
  Text::Text(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_text(createInputPort<std::string>(TEXT_PORT_NAME, [this](Persistence::Data&& newValue) { onTextChanged(std::move(newValue)); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  void Text::onTextChanged(Persistence::Data&& newValue)
  {
    auto textRenderer = getGameObject()->findComponent<Celeste::Rendering::TextRenderer>();
    ASSERT_NOT_NULL(textRenderer);

    if (textRenderer != nullptr)
    {
      textRenderer->setText(std::get<std::string>(newValue));
    }
  }
}