#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"

#include <string>


namespace MCF::Time
{
  class TimeManager;
}

namespace MCF::Money
{
  class MoneyManager;
}

namespace MCF::Family
{
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

  class GameEvent : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(GameEvent, MCFLibraryDllExport);

    public:
      bool canTrigger(
        Time::TimeManager& timeManager, 
        Money::MoneyManager& moneyManager, 
        Family::FamilyManager& familyManager) const;

      void trigger(
        Money::MoneyManager& moneyManager,
        Family::FamilyManager& familyManager,
        Locations::LocationsManager& locationsManager,
        Notifications::NotificationManager& notificationManager) const;
      
      static const char* const CONDITIONS_ELEMENT_NAME;
      static const char* const CONDITION_ELEMENT_NAME;
      static const char* const EFFECTS_ELEMENT_NAME;
      static const char* const EFFECT_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      using Conditions = std::vector<std::unique_ptr<Conditions::Condition>>;
      using Effects = std::vector<std::unique_ptr<Effects::Effect>>;

      Conditions m_conditions;
      Effects m_effects;
  };
}