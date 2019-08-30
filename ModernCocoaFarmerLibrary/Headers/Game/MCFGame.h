#pragma once

#include "Game/Game.h"
#include "Networking/RAII/AutoWSACleanup.h"

#include <memory>


namespace MCF
{
  namespace Managers
  {
    class GameplayManager;
  }

  namespace Debugging
  {
    class SceneBroadcaster;
    class LuaScriptReceiver;
  }

  class MCFGame : public CelesteEngine::Game 
  {
    public:
      MCFGame();
      MCFGame(const MCFGame&) = delete;

      MCFGame& operator=(const MCFGame&) = delete;

      const std::unique_ptr<Managers::GameplayManager>& getGameplayManager() const { return m_gameplayManager; }

    protected:
      void onInitialize() override;
      void onUpdate(float elapsedGameTime) override;
      void onExit() override;

    private:
      using Inherited = CelesteEngine::Game;

      std::unique_ptr<Managers::GameplayManager> m_gameplayManager;
      std::unique_ptr<Debugging::SceneBroadcaster> m_sceneBroadcaster;
      std::unique_ptr<Debugging::LuaScriptReceiver> m_luaScriptReceiver;

      Networking::AutoWSACleanup wsaCleanup;
  };
}