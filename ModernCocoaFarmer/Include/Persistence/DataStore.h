#pragma once

#include "MCFLibraryDllExport.h"
#include "tinyxml2.h"
#include "Assert/Assert.h"
#include "XML/tinyxml2_ext.h"
#include "CelesteStl/Templates/Variant.h"
#include "Persistence/Data.h"

#if _DEBUG
#include <map>
#else
#include <unordered_map>
#endif
#include <functional>
#include <memory>


namespace Celeste
{
  class Path;
}

namespace MCF::Persistence
{
  class DataStore
  {
    private:
#if _DEBUG
      using DataLookup = std::map<std::string, Data>;
#else
      using DataLookup = std::unordered_map<std::string, Data>;
#endif
      
    public:
      MCFLibraryDllExport DataStore();
      MCFLibraryDllExport ~DataStore() = default;
      MCFLibraryDllExport DataStore(DataStore&&) noexcept;
      DataStore(const DataStore&) = delete;
      DataStore& operator=(const DataStore&) = delete;

      size_t getSize() const { return m_dataLookup.size(); }

      MCFLibraryDllExport bool has(const std::string& dataKey) const;

      template <typename T>
      bool is(const std::string& dataKey) const;

      template <typename T>
      T get(const std::string& dataKey, T defaultValue = T()) const;

      template <typename T>
      bool set(const std::string& dataKey, T value);

      MCFLibraryDllExport void serialize(tinyxml2::XMLElement& dataElementRoot) const;
      MCFLibraryDllExport static DataStore deserialize(const tinyxml2::XMLElement& dataElementRoot);

      MCFLibraryDllExport static const char* const DATA_TYPE_ATTRIBUTE_NAME;
      MCFLibraryDllExport static const char* const KEY_ATTRIBUTE_NAME;
      MCFLibraryDllExport static const char* const VALUE_ATTRIBUTE_NAME;

    private:
      DataStore(DataLookup&& data);

      template <typename T>
      bool unsafe_is(const std::string& dataKey) const;

      DataLookup m_dataLookup;

#if _DEBUG
      friend class DebugDataStore;
#endif
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool DataStore::unsafe_is(const std::string& dataKey) const
  {
    return std::holds_alternative<T>(m_dataLookup.at(dataKey));
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool DataStore::is(const std::string& dataKey) const
  {
    return has(dataKey) && unsafe_is<T>(dataKey);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T DataStore::get(const std::string& dataKey, T defaultValue) const
  {
    if (!has(dataKey))
    {
      return defaultValue;
    }

    if (!unsafe_is<T>(dataKey))
    {
      ASSERT_FAIL_MSG(("Type Mismatch.  Expected " + std::to_string(celstl::variant_index<Data, T>()) + ", Actual " + std::to_string(m_dataLookup.at(dataKey).index())).c_str());
      return defaultValue;
    }

    return is<T>(dataKey) ? std::get<T>(m_dataLookup.at(dataKey)) : defaultValue;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool DataStore::set(const std::string& dataKey, T value)
  {
    if (!has(dataKey))
    {
      m_dataLookup.insert(std::make_pair(dataKey, Data(value)));
      return true;
    }
    else if (unsafe_is<T>(dataKey))
    {
      m_dataLookup.at(dataKey) = value;
      return true;
    }

    ASSERT_FAIL_MSG(("Type Mismatch.  Expected " + std::to_string(celstl::variant_index<Data, T>()) + ", Actual " + std::to_string(m_dataLookup.at(dataKey).index())).c_str());
    return false;
  }

#if _DEBUG
  class DebugDataStore
  {
    public:
      DebugDataStore(DataStore& dataStore) : m_dataStore(dataStore) {}

      DataStore::DataLookup& getData() { return m_dataStore.m_dataLookup; }

    private:
      DataStore& m_dataStore;
  };
#endif
}