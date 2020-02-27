#include "Time/TimeNotifier.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Time
{
  REGISTER_SCRIPT(TimeNotifier, 1);

  //------------------------------------------------------------------------------------------------
  TimeNotifier::TimeNotifier() :
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