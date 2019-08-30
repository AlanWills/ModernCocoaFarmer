#pragma once

#include "Objects/ScriptableObject.h"
#include "MCFLibraryDllExport.h"


namespace MCF
{
  namespace Buildings
  {
    class MCFLibraryDllExport Building : public CelesteEngine::ScriptableObject
    {
      DECLARE_SCRIPTABLE_OBJECT(Building)

      public:
        const std::string& getDescription() const { return m_description.getValue(); }

        static const std::string DESCRIPTION_FIELD_NAME;

      private:
        CelesteEngine::ReferenceField<std::string>& m_description;
    };
  }
}