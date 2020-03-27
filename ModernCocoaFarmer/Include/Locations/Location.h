#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Stats/Modifier.h"
#include "Events/Event.h"


namespace Celeste::Resources
{
  class Texture2D;
}

namespace MCF::Money
{
  class MoneyManager;
}

namespace MCF::Family
{
  class Child;
  class FamilyManager;
}

namespace MCF::Locations
{
  class LocationsManager;
}

namespace MCF::Notifications
{
  class NotificationManager;
}

namespace MCF::Stats
{
  class Modifier;
}

namespace MCF::GameEvents
{
  namespace Conditions
  {
    class Condition;
  }

  namespace Effects
  {
    class Effect;
  }
}

namespace MCF::Locations
{
  class Location : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(Location, MCFLibraryDllExport)

    public:
      using ChildSentEvent = Celeste::Event<const Family::Child&>;
      using ChildLeftEvent = Celeste::Event<const Family::Child&>;

      inline const std::string& getDescription() const { return m_description.getValue(); }
      inline const std::string& getChildLeavesNotificationDescription() const { return m_childLeavesNotificationDescription.getValue(); }
      inline observer_ptr<Celeste::Resources::Texture2D> getChildLeavesNotificationIcon() const { return m_childLeavesNotificationIcon.getValue(); }

      inline const Stats::Modifier& getHealthModifier() const { return m_healthModifier; }
      inline const Stats::Modifier& getSafetyModifier() const { return m_safetyModifier; }
      inline const Stats::Modifier& getEducationModifier() const { return m_educationModifier; }
      inline const Stats::Modifier& getHappinessModifier() const { return m_happinessModifier; }
      inline const Stats::Modifier& getMoneyModifier() const { return m_moneyModifier; }

      inline size_t getDaysToComplete() const { return m_daysToComplete.getValue(); }
      size_t getChildTime(const std::string& childName) const;

      void sendChild(Family::Child& child);
      void onDayPassed();

      void checkForChildrenArriving(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationsManager,
        Notifications::NotificationManager& notificationManager);

      void checkForChildrenLeaving(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationsManager,
        Notifications::NotificationManager& notificationManager);

      inline const ChildSentEvent& getOnChildSentEvent() const { return m_onChildSentEvent; }
      inline const ChildLeftEvent& getOnChildLeftEvent() const { return m_onChildLeftEvent; }

      static const std::string DESCRIPTION_FIELD_NAME;
      static const std::string CHILD_LEAVES_NOTIFICATION_DESCRIPTION_FIELD_NAME;
      static const std::string CHILD_LEAVES_NOTIFICATION_ICON_FIELD_NAME;
      static const std::string HEALTH_MODIFIER_FIELD_NAME;
      static const std::string SAFETY_MODIFIER_FIELD_NAME;
      static const std::string EDUCATION_MODIFIER_FIELD_NAME;
      static const std::string HAPPINESS_MODIFIER_FIELD_NAME;
      static const std::string MONEY_MODIFIER_FIELD_NAME;
      static const std::string DAYS_TO_COMPLETE_FIELD_NAME;
      static const std::string CHILD_LEAVES_EFFECTS_ELEMENT_NAME;
      static const std::string CHILD_LEAVES_EFFECT_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      using Effects = std::vector<std::unique_ptr<GameEvents::Effects::Effect>>;
      using ChildDaysSpent = std::tuple<std::reference_wrapper<Family::Child>, size_t>;

      void triggerChildLeavesEffects(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationsManager,
        Notifications::NotificationManager& notificationManager) const;

      Celeste::ReferenceField<std::string>& m_description;
      Celeste::ReferenceField<std::string>& m_childLeavesNotificationDescription;
      Celeste::ValueField<observer_ptr<Celeste::Resources::Texture2D>>& m_childLeavesNotificationIcon;
      Stats::Modifier& m_healthModifier;
      Stats::Modifier& m_safetyModifier;
      Stats::Modifier& m_educationModifier;
      Stats::Modifier& m_happinessModifier;
      Stats::Modifier& m_moneyModifier;
      Celeste::ValueField<size_t>& m_daysToComplete;

      std::vector<std::reference_wrapper<Family::Child>> m_childrenWaitingToArrive;
      std::vector<ChildDaysSpent> m_childrenAtLocation;
      Effects m_childLeavesEffects;

      ChildSentEvent m_onChildSentEvent;
      ChildLeftEvent m_onChildLeftEvent;
  };
}