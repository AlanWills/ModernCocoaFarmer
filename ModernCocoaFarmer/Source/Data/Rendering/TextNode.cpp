#include "Data/Rendering/TextNode.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Objects/GameObject.h"
#include "Rendering/TextRenderer.h"


namespace MCF::Data::Rendering
{
  REGISTER_COMPONENT(TextNode, 30);

  //------------------------------------------------------------------------------------------------
  const std::string TextNode::TEXT_PORT_NAME = "text";

  //------------------------------------------------------------------------------------------------
  TextNode::TextNode(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_text(createInputPort<std::string>(TEXT_PORT_NAME, [this](const NewValue& newValue) { onTextChanged(newValue); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  void TextNode::onTextChanged(const NewValue& newValue)
  {
    auto textRenderer = getGameObject()->findComponent<Celeste::Rendering::TextRenderer>();
    ASSERT_NOT_NULL(textRenderer);

    if (textRenderer != nullptr)
    {
      textRenderer->setText(newValue.get<std::string>());
    }
  }
}