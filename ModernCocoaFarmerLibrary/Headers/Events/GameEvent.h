#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"

#include <string>


namespace MCF::Events
{
  namespace Conditions
  {
    class ICondition;
  }

  class GameEvent : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(GameEvent, MCFLibraryDllExport);

    public:
      bool canTrigger() const;
      void trigger() const;
      
      const std::string& getDescription() const { return m_description.getValue(); }

      static const char* const DESCRIPTION_ATTRIBUTE_NAME;
      static const char* const CONDITIONS_ATTRIBUTE_NAME;

    private:
      using Conditions = std::vector<std::unique_ptr<Conditions::ICondition>>;
      using ConditionsField = CelesteEngine::ReferenceField<Conditions>;

      CelesteEngine::ReferenceField<std::string>& m_description;
      ConditionsField& m_conditions;
  };
}