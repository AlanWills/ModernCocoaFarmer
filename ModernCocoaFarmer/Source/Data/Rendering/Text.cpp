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
    m_text(createInputPort<std::string>(TEXT_PORT_NAME, [this](const NewValue& newValue) { onTextChanged(newValue); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  void Text::onTextChanged(const NewValue& newValue)
  {
    auto textRenderer = getGameObject()->findComponent<Celeste::Rendering::TextRenderer>();
    ASSERT_NOT_NULL(textRenderer);

    if (textRenderer != nullptr)
    {
      textRenderer->setText(newValue.get<std::string>());
    }
  }
}