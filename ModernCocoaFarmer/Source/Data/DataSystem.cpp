#include "Data/DataSystem.h"
#include "Data/Ports/OutputPort.h"
#include "Data/Communication/DataReader.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  void DataSystem::update(float /*elapsedGameTime*/)
  {
    m_inputPortLookup.clear();
    ASSERT(m_pendingConnections.empty());
    
    for (auto& reader : Communication::StringDataReader::m_allocator)
    {
      reader.setValue(get<std::string>(reader.getKey()));
    }
  }

  //------------------------------------------------------------------------------------------------
  void DataSystem::addInputPort(const std::string& fullPath, InputPortBase& inputPort)
  {
    auto exists = m_inputPortLookup.find(fullPath);
    ASSERT(exists == m_inputPortLookup.end());

    if (exists == m_inputPortLookup.end())
    {
      m_inputPortLookup.emplace(fullPath, &inputPort);
      tryResolvePendingConnections();
    }
  }

  //------------------------------------------------------------------------------------------------
  void DataSystem::addPendingConnection(const std::string& fullPath, OutputPortBase& outputPort)
  {
    m_pendingConnections.push_back(std::make_tuple(fullPath, &outputPort));
    tryResolvePendingConnections();
  }

  //------------------------------------------------------------------------------------------------
  void DataSystem::tryResolvePendingConnections()
  {
    for (size_t i = m_pendingConnections.size(); i > 0; --i)
    {
      auto& pendingConnection = m_pendingConnections[i - 1];
      auto inputPortIt = m_inputPortLookup.find(std::get<0>(pendingConnection));

      if (inputPortIt != m_inputPortLookup.end())
      {
        std::get<1>(pendingConnection)->connect(*inputPortIt->second);
        m_pendingConnections.erase(std::next(m_pendingConnections.begin(), i - 1));
      }
    }
  }
}