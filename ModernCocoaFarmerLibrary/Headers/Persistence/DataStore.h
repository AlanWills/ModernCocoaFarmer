#pragma once

#include "tinyxml2.h"
#include "Debug/Assert.h"
#include "XML/tinyxml2_ext.h"

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
      private:
        using Data = std::variant<bool, int>;
        using DataLookup = std::unordered_map<std::string, Data>;
        using SerializeFunction = void (*)(tinyxml2::XMLElement& value, const Data& data);
        using DeserializeFunction = bool (*)(const tinyxml2::XMLAttribute& value, Data& data);

        struct SerializeFunctions
        {
          constexpr size_t size() const { return std::variant_size<Data>(); }

          SerializeFunction m_functions[std::variant_size<Data>()];
        };

        struct DeserializeFunctions
        {
          constexpr size_t size() const { return std::variant_size<Data>(); }

          DeserializeFunction m_functions[std::variant_size<Data>()];
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

        static constexpr SerializeFunctions createSerializeFunctions();
        static constexpr DeserializeFunctions createDeserializeFunctions();

        template <size_t index>
        static constexpr void setSerializeFunction(SerializeFunctions& serializeFunctions);

        template <size_t index>
        static constexpr void setDeserializeFunction(DeserializeFunctions& deserializeFunctions);

        template <>
        static void setDeserializeFunction<0>(DeserializeFunctions& deserializeFunctions);

        template <typename T>
        bool unsafe_is(const std::string& dataKey) const;

        template <typename T>
        static void serialize(tinyxml2::XMLElement& element, const Data& data);

        template <typename T>
        static bool deserialize(const tinyxml2::XMLAttribute& attribute, Data& data);

        DataLookup m_dataLookup;

        static SerializeFunctions m_serializeFunctions;
        static DeserializeFunctions m_deserializeFunctions;
    };

    //------------------------------------------------------------------------------------------------
    template <size_t index>
    static constexpr void DataStore::setSerializeFunction(SerializeFunctions& serializeFunctions)
    {
      serializeFunctions.m_functions[index] = &DataStore::serialize<typename std::variant_alternative<index, Data>::type>;
      setSerializeFunction<index - 1>(serializeFunctions);
    }

    //------------------------------------------------------------------------------------------------
    template <size_t index>
    static constexpr void DataStore::setDeserializeFunction(DeserializeFunctions& deserializeFunctions)
    {
      deserializeFunctions.m_functions[index] = &DataStore::deserialize<typename std::variant_alternative<index, Data>::type>;
      setDeserializeFunction<index - 1>(deserializeFunctions);
    }

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
    void DataStore::serialize(tinyxml2::XMLElement& element, const Data& data)
    {
      element.SetAttribute(VALUE_ATTRIBUTE_NAME, std::get<T>(data));
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    bool DataStore::deserialize(const tinyxml2::XMLAttribute& attribute, Data& data)
    {
      T t;
      if (CelesteEngine::XML::getAttributeData(&attribute, t) == CelesteEngine::XML::XMLValueError::kSuccess)
      {
        data.emplace<T>(t);
        return true;
      }

      ASSERT_FAIL();
      return false;
    }
  }
}