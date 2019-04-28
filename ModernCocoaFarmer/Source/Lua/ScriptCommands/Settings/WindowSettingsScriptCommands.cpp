#include "stdafx.h"

#include "Settings/WindowSettings.h"
#include "Screens/ScreenManager.h"

#include "Lua/ScriptCommands/Settings/WindowSettingsScriptCommands.h"
#include "Lua/LuaState.h"

#include <memory>

using namespace CelesteEngine::Lua;
using namespace MCF::Settings;


namespace MCF
{
  namespace Lua
  {
    namespace Settings
    {
      namespace PlayerSettingsScriptCommands
      {
        namespace Internals
        {
          void apply(const std::string& playerSettingsPath)
          {
            std::unique_ptr<WindowSettings> settings(ScriptableObject::load<WindowSettings>(playerSettingsPath));
            ASSERT(settings.get() != nullptr);

            if (settings != nullptr)
            {
              getScreenManager()->getWindow()->setTitle(settings->getWindowName());
              getScreenManager()->getWindow()->setIcon(Path(Resources::getResourcesDirectory(), settings->getWindowIcon()).as_string());
            }
          }
        }

        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          sol::state& state = LuaState::instance();

          state.new_usertype<WindowSettings>(
            "WindowSettings",
            "apply", &Internals::apply);
        }
      }
    }
  }
}