#pragma once

#include "Persistence/DataStore.h"


namespace MCF::Persistence
{
  class DataArrayHandle
  {
  public:
    DataArrayHandle(DataStore& dataStore, const std::string& key);

    unsigned int getSize() const { return m_size; }
    void setSize(unsigned int size);

    template <typename T>
    bool is(unsigned int index) const;

    template <typename T>
    T get(unsigned int index, T defaultValue = T()) const;

    template <typename T>
    bool set(unsigned int index, T value);

  private:
    bool isIndexValid(unsigned int index) const { return index < m_size; }

    std::string createFormattedSizeKey() const;
    std::string createFormattedElementKey(unsigned int index) const;

    DataStore& m_dataStore;
    std::string m_key;
    unsigned int m_size;
  };


  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool DataArrayHandle::is(unsigned int index) const
  {
    ASSERT(isIndexValid(index));
    return isIndexValid(index) ? m_dataStore.is<T>(createFormattedElementKey(index)) : false;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T DataArrayHandle::get(unsigned int index, T defaultValue) const
  {
    ASSERT(isIndexValid(index));
    return isIndexValid(index) ? m_dataStore.get<T>(createFormattedElementKey(index), defaultValue) : defaultValue;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool DataArrayHandle::set(unsigned int index, T value)
  {
    ASSERT(isIndexValid(index));
    return isIndexValid(index) ? m_dataStore.set<T>(createFormattedElementKey(index), value) : false;
  }
}