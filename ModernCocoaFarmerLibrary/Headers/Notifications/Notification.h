#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"


namespace CelesteEngine::Resources
{
  class Texture2D;
}

namespace MCF::Notifications
{
  class Notification : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(Notification, MCFLibraryDllExport);

    public:
      const std::string& getDescription() const { return m_description.getValue(); }
      const CelesteEngine::Handle<CelesteEngine::Resources::Texture2D>& getIcon() const { return m_icon.getValue(); }

      static const char* const DESCRIPTION_ATTRIBUTE_NAME;
      static const char* const ICON_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ReferenceField<std::string>& m_description;
      CelesteEngine::ReferenceField<CelesteEngine::Handle<CelesteEngine::Resources::Texture2D>>& m_icon;
  };
}