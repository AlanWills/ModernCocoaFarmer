#include "Events/GameEvent.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF::Events
{
  REGISTER_SCRIPTABLE_OBJECT(GameEvent);

  //------------------------------------------------------------------------------------------------
  const char* const GameEvent::DESCRIPTION_ATTRIBUTE_NAME = "description";

  //------------------------------------------------------------------------------------------------
  GameEvent::GameEvent() :
    m_description(createReferenceField<std::string>(DESCRIPTION_ATTRIBUTE_NAME))
  {
  }
}