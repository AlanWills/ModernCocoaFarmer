#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"

#include <string>


namespace CelesteEngine::Resources
{
  class Texture2D;
}

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
        Locations::LocationsManager& locationsManager) const;
      
      const std::string& getDescription() const { return m_description.getValue(); }
      const CelesteEngine::Handle<CelesteEngine::Resources::Texture2D>& getIcon() const { return m_icon.getValue(); }

      static const char* const DESCRIPTION_ATTRIBUTE_NAME;
      static const char* const ICON_ATTRIBUTE_NAME;
      static const char* const CONDITIONS_ELEMENT_NAME;
      static const char* const CONDITION_ELEMENT_NAME;
      static const char* const EFFECTS_ELEMENT_NAME;
      static const char* const EFFECT_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      using Conditions = std::vector<std::unique_ptr<Conditions::Condition>>;
      using Effects = std::vector<std::unique_ptr<Effects::Effect>>;

      CelesteEngine::ReferenceField<std::string>& m_description;
      CelesteEngine::ReferenceField<CelesteEngine::Handle<CelesteEngine::Resources::Texture2D>>& m_icon;
      Conditions m_conditions;
      Effects m_effects;
  };
}