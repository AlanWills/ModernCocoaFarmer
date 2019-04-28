#include "stdafx.h"

#include "Settings/PlayerSettings.h"
#include "Screens/ScreenManager.h"

#include "Lua/ScriptCommands/Settings/PlayerSettingsScriptCommands.h"
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
            std::unique_ptr<PlayerSettings> settings(ScriptableObject::load<PlayerSettings>(playerSettingsPath));
            
            getScreenManager()->getWindow()->setTitle(settings->getWindowName());
          }
        }

        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          sol::state& state = LuaState::instance();

          // make usertype metatable
          state.new_usertype<PlayerSettings>(
            "PlayerSettings",
            "apply", &Internals::apply);
        }
      }
    }
  }
}