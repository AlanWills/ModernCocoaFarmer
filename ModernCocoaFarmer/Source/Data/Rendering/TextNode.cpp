#include "Data/Rendering/TextNode.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Data/Ports/InputPort.h"
#include "Data/Ports/OutputPort.h"
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
    m_text(createInputPort(TEXT_PORT_NAME, type<std::string>()))
  {
  }

  //------------------------------------------------------------------------------------------------
  void TextNode::OnInputPortValueChanged(const std::string& portName, const std::string& newValue)
  {
    ASSERT(portName == TEXT_PORT_NAME);
    if (portName == TEXT_PORT_NAME)
    {
      auto textRenderer = getGameObject()->findComponent<Celeste::Rendering::TextRenderer>();
      ASSERT_NOT_NULL(textRenderer);

      if (textRenderer != nullptr)
      {
        textRenderer->setText(newValue);
      }
    }
  }
}