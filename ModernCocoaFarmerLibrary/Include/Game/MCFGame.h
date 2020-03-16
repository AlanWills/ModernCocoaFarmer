#pragma once

#include "Game/Game.h"
#include "MCFLibraryDllExport.h"
#include "Networking/RAII/AutoWSACleanup.h"

#include <memory>


namespace MCF
{
  namespace Debugging
  {
    class SceneBroadcaster;
    class LuaScriptReceiver;
  }

  class MCFGame : public Celeste::Game 
  {
    public:
      MCFLibraryDllExport MCFGame();
      MCFLibraryDllExport ~MCFGame();
      MCFGame(const MCFGame&) = delete;

      MCFGame& operator=(const MCFGame&) = delete;

    protected:
      void onInitialize() override;
      void onUpdate(float elapsedGameTime) override;
      void onExit() override;

    private:
      using Inherited = Celeste::Game;

      std::unique_ptr<Debugging::SceneBroadcaster> m_sceneBroadcaster;
      std::unique_ptr<Debugging::LuaScriptReceiver> m_luaScriptReceiver;

      Networking::AutoWSACleanup wsaCleanup;
  };
}