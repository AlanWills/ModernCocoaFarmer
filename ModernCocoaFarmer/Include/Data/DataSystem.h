#pragma once

#include "MCFLibraryDllExport.h"
#include "System/ISystem.h"
#include "Persistence/DataStore.h"
#include "CelesteStl/Memory/ObserverPtr.h"


namespace MCF::Data
{
  class InputPortBase;
  class OutputPortBase;

  class DataSystem : public Persistence::DataStore, public Celeste::System::ISystem
  {
    public:
      MCFLibraryDllExport void update(float elapsedGameTime) override;

      void addInputPort(const std::string& fullPath, InputPortBase& inputPort);
      void addPendingConnection(const std::string& fullPath, OutputPortBase& outputPort);

    private:
      void tryResolvePendingConnections();

      std::unordered_map<std::string, observer_ptr<InputPortBase>> m_inputPortLookup;
      std::vector<std::tuple<std::string, observer_ptr<OutputPortBase>>> m_pendingConnections;
  };
}