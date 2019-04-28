#pragma once

#include <string>


namespace MCF
{
  namespace Lua
  {
    namespace Settings
    {
      namespace WindowSettingsScriptCommands
      {
        namespace Internals
        {
          void apply(const std::string& windowSettingsPath);
        }

        void initialize();
      }
    }
  }
}