#include "Events/GameEvent.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Events/Conditions/Condition.h"
#include "XML/Elements/DataConverterListElement.h"


namespace MCF::Events
{
  REGISTER_SCRIPTABLE_OBJECT(GameEvent);

  //------------------------------------------------------------------------------------------------
  const char* const GameEvent::DESCRIPTION_ATTRIBUTE_NAME = "description";
  const char* const GameEvent::CONDITIONS_ELEMENT_NAME = "Conditions";
  const char* const GameEvent::CONDITION_ELEMENT_NAME = "Condition";

  //------------------------------------------------------------------------------------------------
  GameEvent::GameEvent() :
    m_description(createReferenceField<std::string>(DESCRIPTION_ATTRIBUTE_NAME)),
    m_conditions()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool GameEvent::doDeserialize(const tinyxml2::XMLElement* element)
  {
    CelesteEngine::XML::DataConverterListElement<

    return true;
  }

  //------------------------------------------------------------------------------------------------
  void GameEvent::doSerialize(tinyxml2::XMLElement* element) const
  {

  }

  //------------------------------------------------------------------------------------------------
  bool GameEvent::canTrigger(Time::TimeManager& timeManager) const
  {
    for (const auto& condition : m_conditions)
    {
      if (!condition->isConditionMet(timeManager))
      {
        return false;
      }
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  void GameEvent::trigger(Time::TimeManager&) const
  {

  }
}