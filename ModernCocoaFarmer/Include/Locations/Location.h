#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Stats/Modifier.h"
#include "Events/Event.h"


namespace Celeste::Resources
{
  class Texture2D;
}

namespace MCF::Family
{
  class Child;
}

namespace MCF::Stats
{
  class Modifier;
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

      MCFLibraryDllExport void applyModifiers(Family::Child& child);

      inline unsigned int getDaysToComplete() const { return m_daysToComplete.getValue(); }

      MCFLibraryDllExport void sendChild(Family::Child& child);
      MCFLibraryDllExport void leaveChild(Family::Child& child);

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

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      Celeste::ReferenceField<std::string>& m_description;
      Celeste::ReferenceField<std::string>& m_childLeavesNotificationDescription;
      Celeste::ValueField<observer_ptr<Celeste::Resources::Texture2D>>& m_childLeavesNotificationIcon;
      Stats::Modifier& m_healthModifier;
      Stats::Modifier& m_safetyModifier;
      Stats::Modifier& m_educationModifier;
      Stats::Modifier& m_happinessModifier;
      Stats::Modifier& m_moneyModifier;
      Celeste::ValueField<unsigned int>& m_daysToComplete;

      ChildSentEvent m_onChildSentEvent;
      ChildLeftEvent m_onChildLeftEvent;
  };
}