#include "Data/DataSystem.h"
#include "Data/Ports/OutputPort.h"
#include "Data/Communication/DataReader.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  void DataSystem::update(float /*elapsedGameTime*/)
  {
    ASSERT(m_pendingInputPortConnections.empty());
    ASSERT(m_pendingOutputPortConnections.empty());

    for (auto& reader : Communication::DataReader::m_allocator)
    {
      auto changedKeyIt = m_changedKeys.find(reader.getKey());
      if (changedKeyIt != m_changedKeys.end())
      {
        queueUpdate(reader);
      }
    }

    m_changedKeys.clear();

    for (observer_ptr<DataNodeComponent> queuedUpdate : m_queuedUpdates)
    {
      queuedUpdate->update(*this);
    }

    m_queuedUpdates.clear();
  }

  //------------------------------------------------------------------------------------------------
  void DataSystem::addInputPortConnection(InputPort& inputPort, const std::string& fullConnectionPath)
  {
    auto exists = m_pendingOutputPortConnections.find(fullConnectionPath);

    if (exists == m_pendingOutputPortConnections.end())
    {
      // We do not have a pending output port with the same registered connection so we cache the input port
      m_pendingInputPortConnections.emplace(fullConnectionPath, &inputPort);
    }
    else
    {
      // We have a pending output port with the same registered connection so we resolve and remove
      exists->second->connect(inputPort);
      m_pendingOutputPortConnections.erase(exists);
    }
  }

  //------------------------------------------------------------------------------------------------
  void DataSystem::addOutputPortConnection(OutputPort& outputPort, const std::string& fullConnectionPath)
  {
    auto exists = m_pendingInputPortConnections.find(fullConnectionPath);

    if (exists == m_pendingInputPortConnections.end())
    {
      // We do not have a pending input port with the same registered connection so we cache the output port
      m_pendingOutputPortConnections.emplace(fullConnectionPath, &outputPort);
    }
    else
    {
      // We have a pending input port with the same registered connection so we resolve and remove
      outputPort.connect(*exists->second);
      m_pendingInputPortConnections.erase(exists);
    }
  }

  //------------------------------------------------------------------------------------------------
  void DataSystem::queueUpdate(DataNodeComponent& dataNodeComponent)
  {
    m_queuedUpdates.push_back(&dataNodeComponent);
  }

  //------------------------------------------------------------------------------------------------
  Persistence::DataObjectHandle DataSystem::getObject(const std::string& dataKey)
  {
    return Persistence::DataObjectHandle(m_dataStore, dataKey);
  }

  //------------------------------------------------------------------------------------------------
  Persistence::DataArrayHandle DataSystem::getArray(const std::string& dataKey)
  {
    return Persistence::DataArrayHandle(m_dataStore, dataKey);
  }
}