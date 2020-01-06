#include "Events/GameEvent.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Events/Conditions/Condition.h"
#include "DataConverters/Objects/ScriptableObjectDataConverter.h"


namespace MCF::Events
{
  using namespace Conditions;

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
    bool result = true;

    const tinyxml2::XMLElement* conditionsElement = element->FirstChildElement(CONDITIONS_ELEMENT_NAME);
    if (conditionsElement != nullptr)
    {
      for (const tinyxml2::XMLElement* condition : children(conditionsElement, CONDITION_ELEMENT_NAME))
      {
        CelesteEngine::ScriptableObjectDataConverter conditionDataConverter(condition->Name());
        if (conditionDataConverter.convertFromXML(condition))
        {
          auto condition = conditionDataConverter.instantiate<Condition>();
          ASSERT(condition.get() != nullptr);

          if (condition != nullptr)
          {
            m_conditions.emplace_back(condition.release());
          }
        }
        else
        {
          ASSERT_FAIL();
          result = false;
        }
      }
    }

    return result;
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