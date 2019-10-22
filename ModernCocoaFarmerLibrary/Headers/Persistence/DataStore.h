#pragma once

#include "tinyxml2.h"
#include "MCFLibraryDllExport.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>


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
        struct Data
        {
          DataType m_dataType = DataType::kNumDataTypes;

          union
          {
            bool m_bool;
          } m_data;
        };

        using DataLookup = std::unordered_map<std::string, Data>;
        using SerializeFunction = std::function<void(tinyxml2::XMLElement& value, const Data& data)>;
        using SerializeMap = const std::unordered_map<DataType, SerializeFunction>;
        using DeserializeFunction = std::function<bool(const tinyxml2::XMLAttribute& value, Data& data)>;
        using DeserializeMap = const std::unordered_map<DataType, DeserializeFunction>;

      public:
        DataStore();
        ~DataStore();
        DataStore(DataStore&&);
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

        DataLookup m_dataLookup;

        static SerializeMap m_serializeMap;
        static DeserializeMap m_deserializeMap;
    };
  }
}