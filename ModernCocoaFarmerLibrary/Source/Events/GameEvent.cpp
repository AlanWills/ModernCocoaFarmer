#include "Events/GameEvent.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Events/Conditions/ICondition.h"


namespace MCF::Events
{
  REGISTER_SCRIPTABLE_OBJECT(GameEvent);

  //------------------------------------------------------------------------------------------------
  const char* const GameEvent::DESCRIPTION_ATTRIBUTE_NAME = "description";
  const char* const GameEvent::CONDITIONS_ATTRIBUTE_NAME = "conditions";

  //------------------------------------------------------------------------------------------------
  GameEvent::GameEvent() :
    m_description(createReferenceField<std::string>(DESCRIPTION_ATTRIBUTE_NAME)),
    m_conditions(createReferenceField<Conditions>(CONDITIONS_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool GameEvent::canTrigger() const
  {
    for (const auto& condition : m_conditions.getValue())
    {
      if (!condition->isConditionMet())
      {
        return false;
      }
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  void GameEvent::trigger() const
  {

  }
}