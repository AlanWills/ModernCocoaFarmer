#include "Locations/Location.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/Child.h"
#include "GameEvents/Effects/Effect.h"
#include "DataConverters/Objects/ScriptableObjectDataConverter.h"
#include "Notifications/NotificationManager.h"
#include "Notifications/Notification.h"
#include "Money/MoneyManager.h"
#include "Utils/LocaTokens.h"


namespace MCF::Locations
{
  REGISTER_SCRIPTABLE_OBJECT(Location);

  //------------------------------------------------------------------------------------------------
  const std::string Location::DESCRIPTION_FIELD_NAME = "description";
  const std::string Location::CHILD_LEAVES_NOTIFICATION_DESCRIPTION_FIELD_NAME = "child_leaves_notification_description";
  const std::string Location::CHILD_LEAVES_NOTIFICATION_ICON_FIELD_NAME = "child_leaves_notification_icon";
  const std::string Location::HEALTH_MODIFIER_FIELD_NAME = "HealthModifier";
  const std::string Location::SAFETY_MODIFIER_FIELD_NAME = "SafetyModifier";
  const std::string Location::EDUCATION_MODIFIER_FIELD_NAME = "EducationModifier";
  const std::string Location::HAPPINESS_MODIFIER_FIELD_NAME = "HappinessModifier";
  const std::string Location::MONEY_MODIFIER_FIELD_NAME = "MoneyModifier";
  const std::string Location::DAYS_TO_COMPLETE_FIELD_NAME = "days_to_complete";
  const std::string Location::CHILD_LEAVES_EFFECTS_ELEMENT_NAME = "ChildLeavesEffects";
  const std::string Location::CHILD_LEAVES_EFFECT_ELEMENT_NAME = "Effect";

  //------------------------------------------------------------------------------------------------
  Location::Location() :
    m_description(createReferenceField<std::string>(DESCRIPTION_FIELD_NAME)),
    m_childLeavesNotificationDescription(createReferenceField<std::string>(CHILD_LEAVES_NOTIFICATION_DESCRIPTION_FIELD_NAME)),
    m_childLeavesNotificationIcon(createValueField<observer_ptr<Celeste::Resources::Texture2D>>(CHILD_LEAVES_NOTIFICATION_ICON_FIELD_NAME)),
    m_healthModifier(createScriptableObject<Stats::Modifier>(HEALTH_MODIFIER_FIELD_NAME)),
    m_safetyModifier(createScriptableObject<Stats::Modifier>(SAFETY_MODIFIER_FIELD_NAME)),
    m_educationModifier(createScriptableObject<Stats::Modifier>(EDUCATION_MODIFIER_FIELD_NAME)),
    m_happinessModifier(createScriptableObject<Stats::Modifier>(HAPPINESS_MODIFIER_FIELD_NAME)),
    m_moneyModifier(createScriptableObject<Stats::Modifier>(MONEY_MODIFIER_FIELD_NAME)),
    m_daysToComplete(createValueField<unsigned int>(DAYS_TO_COMPLETE_FIELD_NAME)),
    m_childrenWaitingToArrive(),
    m_childrenAtLocation(),
    m_childLeavesEffects(),
    m_onChildSentEvent(),
    m_onChildLeftEvent()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Location::doDeserialize(const tinyxml2::XMLElement* element)
  {
    bool result = true;

    // Effects
    {
      const tinyxml2::XMLElement* effectsElement = element->FirstChildElement(CHILD_LEAVES_EFFECTS_ELEMENT_NAME.c_str());
      if (effectsElement != nullptr)
      {
        for (const tinyxml2::XMLElement* effectElement : Celeste::XML::children(effectsElement, CHILD_LEAVES_EFFECT_ELEMENT_NAME))
        {
          Celeste::ScriptableObjectDataConverter effectDataConverter(effectElement->Name());
          if (effectDataConverter.convertFromXML(effectElement))
          {
            auto effect = effectDataConverter.instantiate<GameEvents::Effects::Effect>();
            ASSERT(effect.get() != nullptr);

            if (effect != nullptr)
            {
              m_childLeavesEffects.emplace_back(std::move(effect));
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
  void Location::sendChild(Family::Child& child)
  {
    m_childrenWaitingToArrive.push_back(std::reference_wrapper<Family::Child>(child));
  }

  //------------------------------------------------------------------------------------------------
  void Location::onDayPassed()
  {
    for (ChildDaysSpent& childDaysSpent : m_childrenAtLocation)
    {
      Family::Child& child = std::get<0>(childDaysSpent).get();
      
      child.applyHealthModifier(m_healthModifier);
      child.applySafetyModifier(m_safetyModifier);
      child.applyEducationModifier(m_educationModifier);
      child.applyHappinessModifier(m_happinessModifier);

      ++std::get<1>(childDaysSpent);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Location::checkForChildrenArriving(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager&,
    Locations::LocationsManager&,
    Notifications::NotificationManager&)
  {
    for (Family::Child& child : m_childrenWaitingToArrive)
    {
      m_childrenAtLocation.emplace_back(std::make_tuple(std::reference_wrapper(child), 0U));
      child.setCurrentLocation(getName());
      moneyManager.applyMoneyModifier(getMoneyModifier());
      m_onChildSentEvent.invoke(child);
    }

    m_childrenWaitingToArrive.clear();
  }

  //------------------------------------------------------------------------------------------------
  void Location::checkForChildrenLeaving(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager& locationsManager,
    Notifications::NotificationManager& notificationManager)
  {
    size_t daysToComplete = getDaysToComplete();

    for (const ChildDaysSpent& childDaysSpent : m_childrenAtLocation)
    {
      if (std::get<1>(childDaysSpent) >= daysToComplete)
      {
        triggerChildLeavesEffects(moneyManager, familyManager, locationsManager, notificationManager);

        std::unique_ptr<Notifications::Notification> notification = ScriptableObject::create<Notifications::Notification>("Child Left " + getName());
        const std::string& description = getChildLeavesNotificationDescription();

        Utils::LocaTokens locaTokens
        {
          { "{CHILD_NAME}", std::get<0>(childDaysSpent).get().getName() }
        };

        notification->setDescription(Utils::substituteLocaTokens(description, locaTokens));
        notification->setIcon(getChildLeavesNotificationIcon());

        notificationManager.sendNotification(*notification);
        m_onChildLeftEvent.invoke(std::get<0>(childDaysSpent));
      }
    }

    m_childrenAtLocation.erase(std::remove_if(m_childrenAtLocation.begin(), m_childrenAtLocation.end(),
      [daysToComplete](const ChildDaysSpent& childDaysSpent)
      {
        return std::get<1>(childDaysSpent) >= daysToComplete;
      }), m_childrenAtLocation.end());
  }

  //------------------------------------------------------------------------------------------------
  void Location::triggerChildLeavesEffects(
    Money::MoneyManager& moneyManager,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager& locationsManager,
    Notifications::NotificationManager& notificationManager) const
  {
    for (const auto& effect : m_childLeavesEffects)
    {
      effect->trigger(moneyManager, familyManager, locationsManager, notificationManager);
    }
  }

  //------------------------------------------------------------------------------------------------
  unsigned int Location::getChildTime(const std::string& childName) const
  {
    auto foundChild = std::find_if(m_childrenAtLocation.begin(), m_childrenAtLocation.end(),
      [&childName](const ChildDaysSpent& childDaysSpent)
      {
        return std::get<0>(childDaysSpent).get().getName() == childName;
      });

    return foundChild != m_childrenAtLocation.end() ? std::get<1>(*foundChild) : 0U;
  }
}