#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"


namespace Celeste::Resources
{
  class Texture2D;
}

namespace MCF::Notifications
{
  class Notification : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(Notification, MCFLibraryDllExport);

    public:
      const std::string& getDescription() const { return m_description.getValue(); }
      void setDescription(const std::string& description) { m_description.setValue(description); }

      inline observer_ptr<Celeste::Resources::Texture2D> getIcon() const { return m_icon.getValue(); }
      inline void setIcon(observer_ptr<Celeste::Resources::Texture2D> icon) { m_icon.setValue(icon); }

      static const char* const DESCRIPTION_ATTRIBUTE_NAME;
      static const char* const ICON_ATTRIBUTE_NAME;

    private:
      Celeste::ReferenceField<std::string>& m_description;
      Celeste::ValueField<observer_ptr<Celeste::Resources::Texture2D>>& m_icon;
  };
}