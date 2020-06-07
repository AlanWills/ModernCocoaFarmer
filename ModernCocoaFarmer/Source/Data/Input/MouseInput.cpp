#include "Data/Input/MouseInput.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Input/MouseInteractionHandler.h"


namespace MCF::Data::Input
{
  REGISTER_COMPONENT(MouseInput, 20);

  //------------------------------------------------------------------------------------------------
  const std::string MouseInput::ON_ENTER_PORT_NAME("on_enter");
  const std::string MouseInput::ON_LEAVE_PORT_NAME("on_leave");
  const std::string MouseInput::ON_LEFT_BUTTON_UP_PORT_NAME("on_left_button_up");

  //------------------------------------------------------------------------------------------------
  MouseInput::MouseInput(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_onEnterPort(createOutputPort<bool>(ON_ENTER_PORT_NAME)),
    m_onLeavePort(createOutputPort<bool>(ON_LEAVE_PORT_NAME)),
    m_onLeftButtonUpPort(createOutputPort<bool>(ON_LEFT_BUTTON_UP_PORT_NAME)),
    m_onEnterEventHandle(StringId()),
    m_onLeaveEventHandle(StringId()),
    m_onLeftButtonUpEventHandle(StringId())
  {
  }

  //------------------------------------------------------------------------------------------------
  MouseInput::~MouseInput()
  {
    auto* mouseInteractionHandler = getGameObject().findComponent<Celeste::Input::MouseInteractionHandler>();
    if (mouseInteractionHandler != nullptr)
    {
      mouseInteractionHandler->getOnEnterEvent().unsubscribe(m_onEnterEventHandle);
      mouseInteractionHandler->getOnLeaveEvent().unsubscribe(m_onLeaveEventHandle);
      mouseInteractionHandler->getOnLeftButtonUpEvent().unsubscribe(m_onLeftButtonUpEventHandle);
    }
  }

  //------------------------------------------------------------------------------------------------
  void MouseInput::update(const DataSystem& /*dataSystem*/)
  {
    if (!m_setupComplete)
    {
      auto* mouseInteractionHandler = getGameObject().findComponent<Celeste::Input::MouseInteractionHandler>();
      ASSERT_NOT_NULL(mouseInteractionHandler);

      if (mouseInteractionHandler != nullptr)
      {
        m_onEnterEventHandle = mouseInteractionHandler->getOnEnterEvent().subscribe([this](Celeste::GameObject& /*gameObject*/)
          {
            m_onEnterPort.setValue(true);
          });

        m_onLeaveEventHandle = mouseInteractionHandler->getOnLeaveEvent().subscribe([this](Celeste::GameObject& /*gameObject*/)
          {
            m_onLeavePort.setValue(true);
          });

        m_onLeftButtonUpEventHandle = mouseInteractionHandler->getOnLeftButtonUpEvent().subscribe([this](Celeste::GameObject& /*gameObject*/)
          {
            m_onLeftButtonUpPort.setValue(true);
          });
      }

      m_setupComplete;
    }
  }
}