#include "Time/TimeNotifier.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Time
{
  REGISTER_COMPONENT(TimeNotifier, 1);

  //------------------------------------------------------------------------------------------------
  TimeNotifier::TimeNotifier(GameObject& gameObject) :
    Inherited(gameObject),
    m_onTimeChangedEvent()
  {
    glfwSwapInterval(0);
    for (size_t i = 0; i < 1000; ++i)
    {
      GameObject* child = new GameObject();
      child->setParent(&gameObject);

      for (size_t j = 0; j < 200; ++j)
      {
        GameObject* grandChild = new GameObject();
        grandChild->setParent(child);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void TimeNotifier::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    m_onTimeChangedEvent.invoke(elapsedGameTime);
  }
}