#include "Data/DataUtils.h"
#include "Data/DataSystem.h"
#include "Game/Game.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  MCF::Data::DataSystem& getDataSystem()
  {
    return *Celeste::Game::current().getSystem<MCF::Data::DataSystem>();
  }
}