#include "stdafx.h"

#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Lua/ScriptCommands//Settings/PlayerSettingsScriptCommands.h"


namespace MCF
{
  namespace Lua
  {
    namespace MCFScriptCommands
    {
      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        Settings::PlayerSettingsScriptCommands::initialize();
      }
    }
  }
}