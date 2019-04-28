#pragma once


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
          void apply(const std::string& playerSettingsPath);
        }

        void initialize();
      }
    }
  }
}