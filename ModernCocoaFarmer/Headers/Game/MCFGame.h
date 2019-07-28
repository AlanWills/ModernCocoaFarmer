#pragma once

#include "Game/Game.h"

#include <memory>


namespace MCF
{
  namespace Debugging
  {
    class SceneBroadcaster;
  }

  class MCFGame : public CelesteEngine::Game 
  {
    public:
      MCFGame();
      MCFGame(const MCFGame&) = delete;

      MCFGame& operator=(const MCFGame&) = delete;

    protected:
      void onInitialize() override;

    private:
      using Inherited = CelesteEngine::Game;

      std::unique_ptr<Debugging::SceneBroadcaster> m_sceneBroadcaster;
  };
}