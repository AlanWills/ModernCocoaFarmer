#include "stdafx.h"

#include "Settings/PlayerSettings.h"
#include "Registries/ScriptableObjectRegistry.h"


namespace MCF
{
  namespace Settings
  {
    REGISTER_SCRIPTABLE_OBJECT(PlayerSettings);

    //------------------------------------------------------------------------------------------------
    PlayerSettings::PlayerSettings() :
      Inherited(),
      m_windowName(createReferenceField<std::string>("window_name", "")),
      m_windowIcon(createHandleField<CelesteEngine::Resources::Texture2D>("window_icon"))
    {
    }
  }
}