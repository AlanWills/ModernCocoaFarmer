#include "stdafx.h"

#include "Settings/WindowSettings.h"
#include "Registries/ScriptableObjectRegistry.h"


namespace MCF
{
  namespace Settings
  {
    REGISTER_SCRIPTABLE_OBJECT(WindowSettings);

    //------------------------------------------------------------------------------------------------
    WindowSettings::WindowSettings() :
      Inherited(),
      m_windowName(createReferenceField<std::string>("window_name", "")),
      m_windowIcon(createReferenceField<std::string>("window_icon"))
    {
    }
  }
}