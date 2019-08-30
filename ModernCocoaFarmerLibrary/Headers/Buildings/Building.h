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
        const std::string& getName() const { return m_name.getValue(); }
        const std::string& getDescription() const { return m_description.getValue(); }

        static const std::string NAME_FIELD_NAME;
        static const std::string DESCRIPTION_FIELD_NAME;

      private:
        CelesteEngine::ReferenceField<std::string>& m_name;
        CelesteEngine::ReferenceField<std::string>& m_description;
    };
  }
}