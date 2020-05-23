#include "Data/Rendering/TextNode.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Objects/GameObject.h"
#include "Rendering/TextRenderer.h"


namespace MCF::Data::Rendering
{
  REGISTER_COMPONENT(TextNode, 30);

  //------------------------------------------------------------------------------------------------
  TextNode::TextNode(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_text(createInputPort<std::string>("text"))
  {
  }

  //------------------------------------------------------------------------------------------------
  void TextNode::OnInputPortValueChanged(const std::string& portName)
  {
    ASSERT(portName == m_text.getName());
    if (portName == m_text.getName())
    {
      auto textRenderer = getGameObject()->findComponent<Celeste::Rendering::TextRenderer>();
      ASSERT_NOT_NULL(textRenderer);

      if (textRenderer != nullptr)
      {
        textRenderer->setText(m_text.getValue());
      }
    }
  }
}