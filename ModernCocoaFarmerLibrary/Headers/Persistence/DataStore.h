#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <variant>


namespace tinyxml2
{
  class XMLElement;
  class XMLAttribute;
}

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
          kNumDataTypes = 1
        };

      private:
        using Data = std::variant<bool>;
        using DataLookup = std::unordered_map<std::string, Data>;
        using SerializeFunction = std::function<void(tinyxml2::XMLElement& value, const Data& data)>;
        using SerializeMap = const std::unordered_map<DataType, SerializeFunction>;
        using DeserializeFunction = std::function<bool(const tinyxml2::XMLAttribute& value, Data& data)>;
        using DeserializeMap = const std::unordered_map<DataType, DeserializeFunction>;

      public:
        DataStore();
        ~DataStore();
        DataStore(DataStore&&) noexcept;
        DataStore(const DataStore&) = delete;
        DataStore& operator=(const DataStore&) = delete;

        size_t getSize() const { return m_dataLookup.size(); }

        bool hasData(const std::string& dataKey) const;

        bool getBool(const std::string& dataKey, bool defaultValue = false) const;
        bool setBool(const std::string& dataKey, bool value);

        void serialize(tinyxml2::XMLElement& dataElementRoot) const;
        static DataStore deserialize(const tinyxml2::XMLElement& dataElementRoot);

        static const char* const DATA_TYPE_ATTRIBUTE_NAME;
        static const char* const KEY_ATTRIBUTE_NAME;
        static const char* const VALUE_ATTRIBUTE_NAME;

      private:
        DataStore(const std::unordered_map<std::string, Data>& data);

        static void serializeBool(tinyxml2::XMLElement& value, const Data& data);
        static bool deserializeBool(const tinyxml2::XMLAttribute& value, Data& data);

        template <typename T>
        bool hasData(const std::string& dataKey) const;

        template <typename T>
        T get(const std::string& dataKey, T defaultValue) const;

        template <typename T>
        bool set(const std::string& dataKey, T value);

        DataLookup m_dataLookup;

        static SerializeMap m_serializeMap;
        static DeserializeMap m_deserializeMap;
    };

    //------------------------------------------------------------------------------------------------
    template <typename T>
    bool DataStore::hasData(const std::string& dataKey) const
    {
      return hasData(dataKey) && std::holds_alternative<T>(m_dataLookup.at(dataKey));
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    T DataStore::get(const std::string& dataKey, T defaultValue) const
    {
      return hasData<T>(dataKey) ? std::get<T>(m_dataLookup.at(dataKey)) : defaultValue;
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    bool DataStore::set(const std::string& dataKey, T value)
    {
      if (!hasData(dataKey))
      {
        m_dataLookup.insert(std::make_pair(dataKey, Data(value)));
        return true;
      }
      else if (std::holds_alternative<T>(m_dataLookup.at(dataKey)))
      {
        m_dataLookup.at(dataKey) = value;
        return true;
      }

      return false;
    }
  }
}