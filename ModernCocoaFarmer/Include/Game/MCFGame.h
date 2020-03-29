#pragma once

#include "Game/Game.h"
#include "MCFLibraryDllExport.h"


namespace MCF
{
  class MCFGame : public Celeste::Game 
  {
    public:
      MCFLibraryDllExport MCFGame();
      MCFLibraryDllExport ~MCFGame();
      MCFGame(const MCFGame&) = delete;

      MCFGame& operator=(const MCFGame&) = delete;

    protected:
      void onInitialize() override;

    private:
      using Inherited = Celeste::Game;
  };
}