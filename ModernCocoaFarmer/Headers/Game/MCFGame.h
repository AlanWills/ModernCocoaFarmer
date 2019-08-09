#pragma once

#include "Game/Game.h"

#include <memory>


namespace MCF
{
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

    protected:
      void onInitialize() override;
      void onUpdate(float elapsedGameTime) override;

    private:
      using Inherited = CelesteEngine::Game;

      std::unique_ptr<Debugging::SceneBroadcaster> m_sceneBroadcaster;
      std::unique_ptr<Debugging::LuaScriptReceiver> m_luaScriptReceiver;
  };
}