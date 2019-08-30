#pragma once

#include <memory>


namespace MCF
{
  namespace Managers
  {
    class GameplayManager;
  }

  namespace Lua
  {
    namespace GameplayManagerScriptCommands
    {
      namespace Internals
      {
        Managers::GameplayManager* getGameplayManager();
      }

      void initialize();
    }
  }
}