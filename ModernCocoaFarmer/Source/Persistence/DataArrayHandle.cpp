#include "Persistence/DataArrayHandle.h"


namespace MCF::Persistence
{
  //------------------------------------------------------------------------------------------------
  DataArrayHandle::DataArrayHandle(Persistence::DataStore& dataStore, const std::string& key) :
    m_dataStore(dataStore),
    m_key(key),
    m_size(0)
  {
    m_size = m_dataStore.get<unsigned int>(createFormattedSizeKey());
  }

  //------------------------------------------------------------------------------------------------
  void DataArrayHandle::setSize(unsigned int size)
  {
    m_size = size;
    m_dataStore.set<unsigned int>(createFormattedSizeKey(), m_size);
  }

  //------------------------------------------------------------------------------------------------
  std::string DataArrayHandle::createFormattedSizeKey() const
  {
    std::string key(m_key);
    key.push_back('.');
    key.append("size");

    return key;
  }

  //------------------------------------------------------------------------------------------------
  std::string DataArrayHandle::createFormattedElementKey(unsigned int index) const
  {
    std::string key(m_key);
    key.push_back('[');
    key.append(std::to_string(index));
    key.push_back(']');

    return key;
  }
}