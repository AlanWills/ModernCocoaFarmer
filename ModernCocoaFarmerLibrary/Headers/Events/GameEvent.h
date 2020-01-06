#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"

#include <string>


namespace MCF::Time
{
  class TimeManager;
}

namespace MCF::Events
{
  namespace Conditions
  {
    class Condition;
  }

  class GameEvent : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(GameEvent, MCFLibraryDllExport);

    public:
      bool canTrigger(Time::TimeManager& tiemManager) const;
      void trigger(Time::TimeManager& timeManager) const;
      
      const std::string& getDescription() const { return m_description.getValue(); }

      static const char* const DESCRIPTION_ATTRIBUTE_NAME;
      static const char* const CONDITIONS_ELEMENT_NAME;
      static const char* const CONDITION_ELEMENT_NAME;

    protected:
      bool doDeserialize(const tinyxml2::XMLElement* element) override;

    private:
      using Conditions = std::vector<std::unique_ptr<Conditions::Condition>>;

      CelesteEngine::ReferenceField<std::string>& m_description;
      Conditions m_conditions;
  };
}