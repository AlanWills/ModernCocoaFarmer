#pragma once

#include "MCFLibraryDllExport.h"
#include "System/ISystem.h"
#include "Persistence/DataStore.h"
#include "Persistence/DataObjectHandle.h"
#include "Persistence/DataArrayHandle.h"
#include "CelesteStl/Memory/ObserverPtr.h"

#include <unordered_set>


namespace MCF::Data
{
  class InputPort;
  class OutputPort;

  class DataSystem : public Celeste::System::ISystem
  {
    public:
      template <typename T>
      T get(const std::string& dataKey, T defaultValue = T()) const
      {
        return m_dataStore.get<T>(dataKey, defaultValue);
      }

      MCFLibraryDllExport Persistence::DataObjectHandle getObject(const std::string& dataKey);
      MCFLibraryDllExport Persistence::DataArrayHandle getArray(const std::string& dataKey);

      template <typename T>
      bool set(const std::string& dataKey, T value);

      MCFLibraryDllExport void update(float elapsedGameTime) override;

      void addInputPort(const std::string& fullPath, InputPort& inputPort);
      void addPendingConnection(const std::string& fullPath, OutputPort& outputPort);

    private:
      void tryResolvePendingConnections();

      std::unordered_map<std::string, observer_ptr<InputPort>> m_inputPortLookup;
      std::vector<std::tuple<std::string, observer_ptr<OutputPort>>> m_pendingConnections;
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