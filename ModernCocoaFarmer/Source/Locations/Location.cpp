#include "Locations/Location.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/Child.h"
#include "Family/FamilyManager.h"
#include "GameEvents/Effects/Effect.h"
#include "DataConverters/Objects/ScriptableObjectDataConverter.h"
#include "Notifications/NotificationManager.h"
#include "Notifications/Notification.h"
#include "Money/MoneyManager.h"
#include "Utils/LocaTokens.h"

using namespace Celeste::XML;


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
  const std::string Location::CHILD_AT_LOCATION_ELEMENT_NAME = "ChildAtLocation";
  const std::string Location::CHILD_AT_LOCATION_NAME_ELEMENT_NAME = "child_name";
  const std::string Location::CHILD_AT_LOCATION_TIME_ELEMENT_NAME = "child_time";
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

    for (const tinyxml2::XMLElement* childAtLocation : children(element, CHILD_AT_LOCATION_ELEMENT_NAME))
    {
      std::string childName;
      XMLValueError error = getAttributeData(childAtLocation, CHILD_AT_LOCATION_NAME_ELEMENT_NAME, childName);

      if (error != XMLValueError::kSuccess)
      {
        ASSERT_FAIL();
        result = false;
        continue;
      }

      unsigned int time = 0;
      error = getAttributeData(childAtLocation, CHILD_AT_LOCATION_TIME_ELEMENT_NAME, time);

      if (error != XMLValueError::kSuccess)
      {
        ASSERT_FAIL();
        result = false;
        continue;
      }

      m_childrenWaitingToArrive.emplace_back(childName, time);
    }

    // Effects
    {
      const tinyxml2::XMLElement* effectsElement = element->FirstChildElement(CHILD_LEAVES_EFFECTS_ELEMENT_NAME.c_str());
      if (effectsElement != nullptr)
      {
        for (const tinyxml2::XMLElement* effectElement : children(effectsElement, CHILD_LEAVES_EFFECT_ELEMENT_NAME))
        {
          m_childLeavesEffects.push_back(deserializeScriptableObject<GameEvents::Effects::Effect>(effectElement));
        }
      }
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  void Location::doSerialize(tinyxml2::XMLElement* element) const
  {
    tinyxml2::XMLDocument* document = element->GetDocument();

    for (const ChildWaitingToArrive& childWaitingToArrive : m_childrenWaitingToArrive)
    {
      tinyxml2::XMLElement* childWaitingElement = document->NewElement(CHILD_AT_LOCATION_ELEMENT_NAME.c_str());
      childWaitingElement->SetAttribute(CHILD_AT_LOCATION_NAME_ELEMENT_NAME.c_str(), std::get<0>(childWaitingToArrive).c_str());
      childWaitingElement->SetAttribute(CHILD_AT_LOCATION_TIME_ELEMENT_NAME.c_str(), std::get<1>(childWaitingToArrive));
      element->InsertEndChild(childWaitingElement);
    }

    for (const ChildAtLocation& childDaysSpent : m_childrenAtLocation)
    {
      tinyxml2::XMLElement* childWaitingElement = document->NewElement(CHILD_AT_LOCATION_ELEMENT_NAME.c_str());
      childWaitingElement->SetAttribute(CHILD_AT_LOCATION_NAME_ELEMENT_NAME.c_str(), std::get<0>(childDaysSpent).get().getName().c_str());
      childWaitingElement->SetAttribute(CHILD_AT_LOCATION_TIME_ELEMENT_NAME.c_str(), std::get<1>(childDaysSpent));
      element->InsertEndChild(childWaitingElement);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Location::sendChild(const std::string& childName)
  {
    m_childrenWaitingToArrive.push_back(std::make_tuple(childName, 0U));
  }

  //------------------------------------------------------------------------------------------------
  const Family::Child& Location::getChildAtLocation(size_t childIndex) const
  {
    ASSERT(childIndex < m_childrenAtLocation.size());
    return std::get<0>(m_childrenAtLocation.at(childIndex));
  }

  //------------------------------------------------------------------------------------------------
  void Location::onDayPassed()
  {
    for (ChildAtLocation& childDaysSpent : m_childrenAtLocation)
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
    Money::MoneyManager&,
    Family::FamilyManager& familyManager,
    Locations::LocationsManager&,
    Notifications::NotificationManager&)
  {
    for (const ChildWaitingToArrive& childWaitingToArrive : m_childrenWaitingToArrive)
    {
      observer_ptr<Family::Child> child = familyManager.findChild(std::get<0>(childWaitingToArrive));
      ASSERT_NOT_NULL(child);

      if (child != nullptr)
      {
        m_childrenAtLocation.emplace_back(std::make_tuple(std::reference_wrapper(*child), 0U));
        child->setCurrentLocation(getName());
        m_onChildSentEvent.invoke(*child);
      }
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

    for (const ChildAtLocation& childDaysSpent : m_childrenAtLocation)
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
      [daysToComplete](const ChildAtLocation& childDaysSpent)
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
      effect.get().trigger(moneyManager, familyManager, locationsManager, notificationManager);
    }
  }

  //------------------------------------------------------------------------------------------------
  unsigned int Location::getChildTime(const std::string& childName) const
  {
    auto foundChild = std::find_if(m_childrenAtLocation.begin(), m_childrenAtLocation.end(),
      [&childName](const ChildAtLocation& childDaysSpent)
      {
        return std::get<0>(childDaysSpent).get().getName() == childName;
      });

    return foundChild != m_childrenAtLocation.end() ? std::get<1>(*foundChild) : 0U;
  }
}