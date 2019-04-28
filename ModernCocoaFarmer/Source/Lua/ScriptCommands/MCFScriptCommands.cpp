#include "stdafx.h"

#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "Lua/ScriptCommands//Settings/WindowSettingsScriptCommands.h"


namespace MCF
{
  namespace Lua
  {
    namespace MCFScriptCommands
    {
      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        Settings::WindowSettingsScriptCommands::initialize();
      }
    }
  }
}