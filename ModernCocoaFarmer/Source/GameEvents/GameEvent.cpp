#include "GameEvents/GameEvent.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "DataConverters/Objects/ScriptableObjectDataConverter.h"
#include "GameEvents/Conditions/Condition.h"
#include "GameEvents/Effects/Effect.h"


namespace MCF::GameEvents
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
        for (const tinyxml2::XMLElement* conditionElement : Celeste::XML::children(conditionsElement, CONDITION_ELEMENT_NAME))
        {
          Celeste::ScriptableObjectDataConverter conditionDataConverter(conditionElement->Name());
          if (conditionDataConverter.convertFromXML(conditionElement))
          {
            auto condition = conditionDataConverter.instantiate<Condition>();
            ASSERT(condition != nullptr);

            if (condition != nullptr)
            {
              addCondition(std::move(condition));
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
        for (const tinyxml2::XMLElement* effectElement : Celeste::XML::children(effectsElement, EFFECT_ELEMENT_NAME))
        {
          Celeste::ScriptableObjectDataConverter effectDataConverter(effectElement->Name());
          if (effectDataConverter.convertFromXML(effectElement))
          {
            auto effect = effectDataConverter.instantiate<Effect>();
            ASSERT(effect != nullptr);

            if (effect != nullptr)
            {
              addEffect(std::move(effect));
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
  void GameEvent::addCondition(std::unique_ptr<Condition>&& condition)
  {
    m_conditions.emplace_back(std::move(condition));
  }

  //------------------------------------------------------------------------------------------------
  void GameEvent::addEffect(std::unique_ptr<Effect>&& effect)
  {
    m_effects.emplace_back(std::move(effect));
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