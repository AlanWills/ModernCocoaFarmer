#include "Data/DataSystem.h"
#include "Data/Ports/OutputPort.h"
#include "Data/Communication/DataReader.h"
#include "CelesteStl/Templates/Variant.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  using Data = Persistence::Data;
  using DataReaderSetters = celstl::VariantFunctions<Data, void, Persistence::DataStore&, Communication::DataReader&>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct DataReaderSetter
  {
    static void execute(Persistence::DataStore& dataStore, Communication::DataReader& reader)
    {
      reader.setValue(dataStore.get<T>(reader.getKey()));
    }
  };

  static DataReaderSetters s_dataReaderSetters = celstl::createVariantFunctions<DataReaderSetters, DataReaderSetter>();

  //------------------------------------------------------------------------------------------------
  void DataSystem::update(float /*elapsedGameTime*/)
  {
    m_inputPortLookup.clear();
    ASSERT(m_pendingConnections.empty());
    
    for (auto& reader : Communication::DataReader::m_allocator)
    {
      auto changedKeyIt = m_changedKeys.find(reader.getKey());
      if (changedKeyIt != m_changedKeys.end())
      {
        if (reader.getType() < s_dataReaderSetters.size())
        {
          s_dataReaderSetters.m_functions[reader.getType()](m_dataStore, reader);
        }
      }
    }

    m_changedKeys.clear();
  }

  //------------------------------------------------------------------------------------------------
  void DataSystem::addInputPort(const std::string& fullPath, InputPort& inputPort)
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
  void DataSystem::addPendingConnection(const std::string& fullPath, OutputPort& outputPort)
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