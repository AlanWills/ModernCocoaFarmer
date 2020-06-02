#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataSystem.h"


namespace MCF::Data
{
  class ObjectRef
  {
    public:
      MCFLibraryDllExport ObjectRef(DataSystem& dataSystem, const std::string& key);

      template <typename T>
      T get(const std::string& elementKey, T defaultValue = T()) const;

      template <typename T>
      bool set(const std::string& elementKey, T value);

    private:
      MCFLibraryDllExport std::string createFormattedElementKey(const std::string& elementKey) const;

      DataSystem& m_dataSystem;
      std::string m_key;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T ObjectRef::get(const std::string& elementKey, T defaultValue) const
  {
    return m_dataSystem.get<T>(createFormattedElementKey(elementKey), defaultValue);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool ObjectRef::set(const std::string& elementKey, T value)
  {
    return m_dataSystem.set<T>(createFormattedElementKey(elementKey), value);
  }
}