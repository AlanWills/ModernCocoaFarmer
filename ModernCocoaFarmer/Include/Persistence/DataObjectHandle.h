#pragma once

#include "MCFLibraryDllExport.h"
#include "Persistence/DataStore.h"


namespace MCF::Persistence
{
  class DataObjectHandle
  {
    public:
      MCFLibraryDllExport DataObjectHandle(DataStore& dataStore, const std::string& key);

      MCFLibraryDllExport bool has(const std::string& elementKey) const;

      template <typename T>
      bool is(const std::string& elementKey) const;

      template <typename T>
      T get(const std::string& elementKey, T defaultValue = T()) const;

      template <typename T>
      bool set(const std::string& elementKey, T value);

    private:
      MCFLibraryDllExport std::string createFormattedElementKey(const std::string & elementKey) const;

      DataStore& m_dataStore;
      std::string m_key;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool DataObjectHandle::is(const std::string& elementKey) const
  {
    return m_dataStore.is<T>(createFormattedElementKey(elementKey));
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T DataObjectHandle::get(const std::string& elementKey, T defaultValue) const
  {
    return m_dataStore.get<T>(createFormattedElementKey(elementKey), defaultValue);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool DataObjectHandle::set(const std::string& elementKey, T value)
  {
    return m_dataStore.set<T>(createFormattedElementKey(elementKey), value);
  }
}