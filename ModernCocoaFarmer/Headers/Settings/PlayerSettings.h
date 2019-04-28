#pragma once

#include "Objects/ScriptableObject.h"
#include "Resources/2D/Texture2D.h"

#include <string>


namespace MCF
{
  namespace Settings
  {
    class PlayerSettings : public CelesteEngine::ScriptableObject
    {
      DECLARE_SCRIPTABLE_OBJECT(PlayerSettings)

      public:
        const std::string& getWindowName() const { return m_windowName->getValue(); }
        Handle<CelesteEngine::Resources::Texture2D> getWindowIcon() const { return m_windowIcon->getValue(); }

      private:
        using Inherited = CelesteEngine::ScriptableObject;

        ReferenceField<std::string>* m_windowName;
        HandleField<CelesteEngine::Resources::Texture2D>* m_windowIcon;
    };
  }
}