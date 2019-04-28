#pragma once

#include "Objects/ScriptableObject.h"
#include "Resources/2D/Texture2D.h"

#include <string>


namespace MCF
{
  namespace Settings
  {
    class WindowSettings : public CelesteEngine::ScriptableObject
    {
      DECLARE_SCRIPTABLE_OBJECT(WindowSettings)

      public:
        const std::string& getWindowName() const { return m_windowName->getValue(); }
        const std::string& getWindowIcon() const { return m_windowIcon->getValue(); }

      private:
        using Inherited = CelesteEngine::ScriptableObject;

        ReferenceField<std::string>* m_windowName;
        ReferenceField<std::string>* m_windowIcon;
    };
  }
}