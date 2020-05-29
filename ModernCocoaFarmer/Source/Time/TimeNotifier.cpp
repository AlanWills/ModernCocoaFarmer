#include "Time/TimeNotifier.h"
#include "Time/TimeUtils.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Time
{
  REGISTER_COMPONENT(TimeNotifier, 1);

  //------------------------------------------------------------------------------------------------
  TimeNotifier::TimeNotifier(GameObject& gameObject) :
    Inherited(gameObject),
    m_onTimeChangedEvent()
  {
  }

  //------------------------------------------------------------------------------------------------
  void TimeNotifier::update()
  {
    Inherited::update();

    m_onTimeChangedEvent.invoke(Celeste::Time::getElapsedDeltaTime());
  }
}