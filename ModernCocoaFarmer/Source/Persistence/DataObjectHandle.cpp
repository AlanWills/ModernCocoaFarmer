#include "Persistence/DataObjectHandle.h"


namespace MCF::Persistence
{
  //------------------------------------------------------------------------------------------------
  DataObjectHandle::DataObjectHandle(Persistence::DataStore& dataStore, const std::string& key) :
    m_dataStore(dataStore),
    m_key(key)
  {
  }

  //------------------------------------------------------------------------------------------------
  bool DataObjectHandle::has(const std::string& elementKey) const
  {
    return m_dataStore.has(createFormattedElementKey(elementKey));
  }

  //------------------------------------------------------------------------------------------------
  std::string DataObjectHandle::createFormattedElementKey(const std::string& elementKey) const
  {
    std::string key(m_key);
    key.push_back('.');
    key.append(elementKey);

    return key;
  }
}