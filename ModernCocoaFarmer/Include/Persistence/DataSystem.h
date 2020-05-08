#pragma once

#include "MCFLibraryDllExport.h"
#include "System/ISystem.h"
#include "Persistence/DataStore.h"


namespace MCF::Persistence
{
  class DataSystem : public DataStore, public Celeste::System::ISystem
  {
    public:
      MCFLibraryDllExport void update(float elapsedGameTime) override;
  };
}