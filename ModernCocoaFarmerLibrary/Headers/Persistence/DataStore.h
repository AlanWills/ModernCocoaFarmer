#pragma once

#include "tinyxml2.h"
#include "Debug/Assert.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <variant>
#include <array>


namespace CelesteEngine
{
  class Path;
}

namespace MCF
{
  namespace Persistence
  {
    class DataStore
    {
      public:
        enum class DataType : unsigned int
        {
          kBool = 0,
          kInt = 1,
          kNumDataTypes = 2
        };

      private:
        using Data = std::variant<bool, int>;
        using DataLookup = std::unordered_map<std::string, Data>;
        using SerializeFunction = void (*)(tinyxml2::XMLElement& value, const Data& data);
        using DeserializeFunction = std::function<bool(const tinyxml2::XMLAttribute& value, Data& data)>;
        using DeserializeMap = const std::unordered_map<DataType, DeserializeFunction>;

        struct SerializeMap
        {
          constexpr size_t size() const { return std::variant_size<Data>(); }

          SerializeFunction m_functions[std::variant_size<Data>()];
        };

      public:
        DataStore();
        ~DataStore() = default;
        DataStore(DataStore&&) noexcept;
        DataStore(const DataStore&) = delete;
        DataStore& operator=(const DataStore&) = delete;

        size_t getSize() const { return m_dataLookup.size(); }

        bool has(const std::string& dataKey) const;

        template <typename T>
        bool is(const std::string& dataKey) const;

        template <typename T>
        T get(const std::string& dataKey, T defaultValue = T()) const;

        template <typename T>
        bool set(const std::string& dataKey, T value);

        void serialize(tinyxml2::XMLElement& dataElementRoot) const;
        static DataStore deserialize(const tinyxml2::XMLElement& dataElementRoot);

        static const char* const DATA_TYPE_ATTRIBUTE_NAME;
        static const char* const KEY_ATTRIBUTE_NAME;
        static const char* const VALUE_ATTRIBUTE_NAME;

      private:
        DataStore(const std::unordered_map<std::string, Data>& data);

        static constexpr SerializeMap createSerializeMap();

        template <size_t index>
        static constexpr void setSerializeFunction(SerializeMap& serializeMap)
        {
          serializeMap.m_functions[index] = &DataStore::serialize<typename std::variant_alternative<index, Data>::type>;
          setSerializeFunction<index - 1>(serializeMap);
        }

        template <>
        static void setSerializeFunction<0>(SerializeMap& serializeMap)
        {
          serializeMap.m_functions[0] = &DataStore::serialize<typename std::variant_alternative<0, Data>::type>;
        }

        template <typename T>
        bool unsafe_is(const std::string& dataKey) const;

        template <typename T>
        static void serialize(tinyxml2::XMLElement& value, const Data& data);

        static bool deserializeBool(const tinyxml2::XMLAttribute& value, Data& data);
        static bool deserializeInt(const tinyxml2::XMLAttribute& value, Data& data);

        DataLookup m_dataLookup;

        static SerializeMap m_serializeMap;
        static DeserializeMap m_deserializeMap;
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

      return false;
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    void DataStore::serialize(tinyxml2::XMLElement& value, const Data& data)
    {
      value.SetAttribute(VALUE_ATTRIBUTE_NAME, std::get<T>(data));
    }
  }
}