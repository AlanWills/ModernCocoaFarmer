#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Stats/ChildModifier.h"


namespace CelesteEngine::Resources
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

namespace MCF::Events
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
  class Location : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(Location, MCFLibraryDllExport)

    public:
      using ChildSentEvent = CelesteEngine::Event<const Family::Child&>;
      using ChildLeftEvent = CelesteEngine::Event<const Family::Child&>;

      const std::string& getPrefab() const { return m_prefab.getValue(); }
      const std::string& getDescription() const { return m_description.getValue(); }
      const std::string& getChildLeavesNotificationDescription() const { return m_childLeavesNotificationDescription.getValue(); }
      CelesteEngine::Handle<CelesteEngine::Resources::Texture2D> getChildLeavesNotificationIcon() const { return m_childLeavesNotificationIcon.getValue(); }

      const Stats::ChildModifier& getHealthModifier() const { return m_healthModifier; }
      const Stats::ChildModifier& getSafetyModifier() const { return m_safetyModifier; }
      const Stats::ChildModifier& getEducationModifier() const { return m_educationModifier; }
      const Stats::ChildModifier& getHappinessModifier() const { return m_happinessModifier; }
      const Stats::Modifier& getMoneyModifier() const { return m_moneyModifier; }

      size_t getDaysToComplete() const { return m_daysToComplete.getValue(); }

      void sendChild(Family::Child& child);
      void onDayPassed();
      void checkForChildrenLeaving(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationsManager,
        Notifications::NotificationManager& notificationManager);

      const ChildSentEvent& getOnChildSentEvent() const { return m_onChildSentEvent; }
      const ChildLeftEvent& getOnChildLeftEvent() const { return m_onChildLeftEvent; }

      static const std::string PREFAB_FIELD_NAME;
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
      using Effects = std::vector<std::unique_ptr<Events::Effects::Effect>>;
      using ChildDaysSpent = std::tuple<std::reference_wrapper<Family::Child>, size_t>;

      void triggerChildLeavesEffects(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationsManager,
        Notifications::NotificationManager& notificationManager) const;

      CelesteEngine::ReferenceField<std::string>& m_prefab;
      CelesteEngine::ReferenceField<std::string>& m_description;
      CelesteEngine::ReferenceField<std::string>& m_childLeavesNotificationDescription;
      CelesteEngine::ValueField<CelesteEngine::Handle<CelesteEngine::Resources::Texture2D>>& m_childLeavesNotificationIcon;
      Stats::ChildModifier& m_healthModifier;
      Stats::ChildModifier& m_safetyModifier;
      Stats::ChildModifier& m_educationModifier;
      Stats::ChildModifier& m_happinessModifier;
      Stats::Modifier& m_moneyModifier;
      CelesteEngine::ValueField<size_t>& m_daysToComplete;

      std::vector<ChildDaysSpent> m_children;
      Effects m_childLeavesEffects;

      ChildSentEvent m_onChildSentEvent;
      ChildLeftEvent m_onChildLeftEvent;
  };
}