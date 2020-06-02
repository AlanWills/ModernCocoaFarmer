#pragma once

#include "MCFLibraryDllExport.h"
#include "System/ISystem.h"
#include "Persistence/DataStore.h"
#include "CelesteStl/Memory/ObserverPtr.h"

#include <unordered_set>


namespace MCF::Data
{
  class InputPort;
  class OutputPort;
  class DataNodeComponent;

  class DataSystem : public Celeste::System::ISystem
  {
    public:
      template <typename T>
      T get(const std::string& dataKey, T defaultValue = T()) const
      {
        return m_dataStore.get<T>(dataKey, defaultValue);
      }

      template <typename T>
      bool set(const std::string& dataKey, T value);

      MCFLibraryDllExport void update(float elapsedGameTime) override;

      void addInputPortConnection(InputPort& inputPort, const std::string& fullConnectionPath);
      void addOutputPortConnection(OutputPort& outputPort, const std::string& fullConnectionPath);
      void queueUpdate(DataNodeComponent& dataNodeComponent);

    private:
      std::unordered_map<std::string, observer_ptr<InputPort>> m_pendingInputPortConnections;
      std::unordered_map<std::string, observer_ptr<OutputPort>> m_pendingOutputPortConnections;
      std::vector<observer_ptr<DataNodeComponent>> m_queuedUpdates;
      std::unordered_set<std::string> m_changedKeys;

      MCF::Persistence::DataStore m_dataStore;

#if _DEBUG
      friend class DebugDataSystem;
#endif
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool DataSystem::set(const std::string& dataKey, T value)
  {
    if (m_dataStore.set<T>(dataKey, value))
    {
      m_changedKeys.insert(dataKey);
      return true;
    }

    return false;
  }

#if _DEBUG
  //------------------------------------------------------------------------------------------------
  class DebugDataSystem
  {
    public:
      DebugDataSystem(DataSystem& dataSystem) : 
        m_dataSystem(dataSystem),
        m_dataStore(dataSystem.m_dataStore)
      {
      }

      DataSystem& getDataSystem() { return m_dataSystem; }
      auto& getData() { return m_dataStore.getData(); }

    private:
      DataSystem& m_dataSystem;
      Persistence::DebugDataStore m_dataStore;
  };
#endif
}