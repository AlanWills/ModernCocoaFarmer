#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"

#include <string>


namespace MCF::Events
{
  class GameEvent : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(GameEvent, MCFLibraryDllExport);

    public:
      const std::string& getDescription() const { return m_description.getValue(); }

      static const char* const DESCRIPTION_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ReferenceField<std::string>& m_description;
  };
}