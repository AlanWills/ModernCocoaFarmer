#include "Time/TimeNotifier.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Time
{
  REGISTER_UNMANAGED_COMPONENT(TimeNotifier, 1);

  //------------------------------------------------------------------------------------------------
  TimeNotifier::TimeNotifier(GameObject& gameObject) :
    Inherited(gameObject),
    m_onTimeChangedEvent()
  {
  }

  //------------------------------------------------------------------------------------------------
  void TimeNotifier::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    m_onTimeChangedEvent.invoke(elapsedGameTime);
  }
}