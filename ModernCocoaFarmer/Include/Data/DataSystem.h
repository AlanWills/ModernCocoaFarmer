#pragma once

#include "MCFLibraryDllExport.h"
#include "System/ISystem.h"
#include "Persistence/DataStore.h"


namespace MCF::Data
{
  class DataSystem : public Persistence::DataStore, public Celeste::System::ISystem
  {
    public:
      MCFLibraryDllExport void update(float elapsedGameTime) override;
  };
}