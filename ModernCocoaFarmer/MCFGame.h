#pragma once

#include "Game/Game.h"


namespace MCF
{
  class MCFGame : public Celeste::Game 
  {
    public:
      MCFGame();
      ~MCFGame();
      MCFGame(const MCFGame&) = delete;

      MCFGame& operator=(const MCFGame&) = delete;

    protected:
      void onInitialize() override;
      void onInitializeDolce(Dolce::IDolce& dolce) override;

    private:
      using Inherited = Celeste::Game;
  };
}