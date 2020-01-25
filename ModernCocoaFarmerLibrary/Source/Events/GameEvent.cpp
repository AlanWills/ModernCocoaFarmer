#include "Events/GameEvent.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "DataConverters/Objects/ScriptableObjectDataConverter.h"
#include "Events/Conditions/Condition.h"
#include "Events/Effects/Effect.h"


namespace MCF::Events
{
  using namespace Conditions;
  using namespace Effects;

  REGISTER_SCRIPTABLE_OBJECT(GameEvent);

  //------------------------------------------------------------------------------------------------
  const char* const GameEvent::CONDITIONS_ELEMENT_NAME = "Conditions";
  const char* const GameEvent::CONDITION_ELEMENT_NAME = "Condition";
  const char* const GameEvent::EFFECTS_ELEMENT_NAME = "Effects";
  const char* const GameEvent::EFFECT_ELEMENT_NAME = "Effect";

  //------------------------------------------------------------------------------------------------
  GameEvent::GameEvent() :
    m_conditions(),
    m_effects()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool GameEvent::doDeserialize(const tinyxml2::XMLElement* element)
  {
    bool result = true;

    // Conditions
    {
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
              m_conditions.emplace_back(std::move(condition));
            }
          }
          else
          {
            ASSERT_FAIL();
            result = false;
          }
        }
      }
    }

    // Effects
    {
      const tinyxml2::XMLElement* effectsElement = element->FirstChildElement(EFFECTS_ELEMENT_NAME);
      if (effectsElement != nullptr)
      {
        for (const tinyxml2::XMLElement* effectElement : children(effectsElement, EFFECT_ELEMENT_NAME))
        {
          CelesteEngine::ScriptableObjectDataConverter effectDataConverter(effectElement->Name());
          if (effectDataConverter.convertFromXML(effectElement))
          {
            auto effect = effectDataConverter.instantiate<Effect>();
            ASSERT(effect.get() != nullptr);

            if (effect != nullptr)
            {
              m_effects.emplace_back(effect.release());
            }
          }
          else
          {
            ASSERT_FAIL();
            result = false;
          }
        }
      }
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  bool GameEvent::canTrigger(
    Time::TimeManager& timeManager,
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager) const
  {
    for (const auto& condition : m_conditions)
    {
      if (!condition->isConditionMet(timeManager, moneyManager, familyManager))
      {
        return false;
      }
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  void GameEvent::trigger(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager& locationsManager,
    Notifications::NotificationManager& notificationManager) const
  {
    for (const auto& effect : m_effects)
    {
      effect->trigger(moneyManager, familyManager, locationsManager, notificationManager);
    }
  }
}