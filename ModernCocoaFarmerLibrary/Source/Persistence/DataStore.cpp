#include "Persistence/DataStore.h"
#include "Debug/Assert.h"
#include "XML/ChildXMLElementWalker.h"


namespace MCF
{
  namespace Persistence
  {
    const char* const DataStore::DATA_TYPE_ATTRIBUTE_NAME = "data_type";
    const char* const DataStore::KEY_ATTRIBUTE_NAME = "key";
    const char* const DataStore::VALUE_ATTRIBUTE_NAME = "value";

    DataStore::SerializeMap DataStore::m_serializeMap
    {
      { DataStore::DataType::kBool, &DataStore::serialize<bool> },
      { DataStore::DataType::kInt, &DataStore::serialize<int> }
    };

    DataStore::DeserializeMap DataStore::m_deserializeMap
    {
      { DataStore::DataType::kBool, &DataStore::deserializeBool },
      { DataStore::DataType::kInt, &DataStore::deserializeInt }
    };

    //------------------------------------------------------------------------------------------------
    DataStore::DataStore() :
      DataStore(DataLookup())
    {
    }

    //------------------------------------------------------------------------------------------------
    DataStore::DataStore(const std::unordered_map<std::string, Data>& data) :
      m_dataLookup(data)
    {
      ASSERT(m_serializeMap.size() == static_cast<size_t>(DataType::kNumDataTypes));
      ASSERT(m_deserializeMap.size() == static_cast<size_t>(DataType::kNumDataTypes));
    }

    //------------------------------------------------------------------------------------------------
    DataStore::~DataStore()
    {
      /*for (const auto& dataPair : m_dataLookup)
      {
        if (dataPair.second.m_dataType == DataType::kString)
        {
          delete dataPair.second.m_data.m_string;
        }
      }*/
    }

    //------------------------------------------------------------------------------------------------
    DataStore::DataStore(DataStore&& rhs) noexcept :
      m_dataLookup(std::move(rhs.m_dataLookup))
    {
    }

    //------------------------------------------------------------------------------------------------
    bool DataStore::has(const std::string& dataKey) const
    {
      return m_dataLookup.find(dataKey) != m_dataLookup.end();
    }

    //------------------------------------------------------------------------------------------------
    void DataStore::serialize(tinyxml2::XMLElement& dataElementRoot) const
    {
      for (const auto& dataPair : m_dataLookup)
      {
        tinyxml2::XMLElement* element = dataElementRoot.GetDocument()->NewElement("Data");
        dataElementRoot.InsertEndChild(element);

        DataType dataType = static_cast<DataType>(dataPair.second.index());

        element->SetAttribute(KEY_ATTRIBUTE_NAME, dataPair.first.c_str());
        element->SetAttribute(DATA_TYPE_ATTRIBUTE_NAME, static_cast<unsigned int>(dataType));
        
        if (m_serializeMap.find(dataType) != m_serializeMap.end())
        {
          m_serializeMap.at(dataType)(*element, dataPair.second);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    DataStore DataStore::deserialize(const tinyxml2::XMLElement& dataElementRoot)
    {
      std::unordered_map<std::string, Data> dataLookup;

      for (const auto& element : CelesteEngine::XML::children(&dataElementRoot))
      {
        unsigned int defaultDataType = static_cast<unsigned int>(DataType::kNumDataTypes);
        DataType dataType = static_cast<DataType>(element->UnsignedAttribute(DATA_TYPE_ATTRIBUTE_NAME, defaultDataType));
        bool deserializeFuncExists = m_deserializeMap.find(dataType) != m_deserializeMap.end();

        ASSERT(deserializeFuncExists);
        if (deserializeFuncExists)
        {
          const char* key = element->Attribute(KEY_ATTRIBUTE_NAME);
          ASSERT(key != nullptr);

          const tinyxml2::XMLAttribute* valueAttr = element->FindAttribute(VALUE_ATTRIBUTE_NAME);
          ASSERT(valueAttr != nullptr);
          
          // Check key and value exists, the key is unique and the value deserializes properly
          Data data;
          if (key != nullptr && valueAttr != nullptr && 
              dataLookup.find(key) == dataLookup.end() &&
              m_deserializeMap.at(dataType)(*valueAttr, data))
          {
            dataLookup.insert(std::make_pair(key, data));
          }
        }
      }
      
      return DataStore(dataLookup);
    }
    
    //------------------------------------------------------------------------------------------------
    bool DataStore::deserializeBool(const tinyxml2::XMLAttribute& value, Data& data)
    {
      bool t = false;
      if (value.QueryBoolValue(&t) == tinyxml2::XMLError::XML_SUCCESS)
      {
        data.emplace<bool>(t);
        return true;
      }

      ASSERT_FAIL();
      return false;
    }

    //------------------------------------------------------------------------------------------------
    bool DataStore::deserializeInt(const tinyxml2::XMLAttribute& value, Data& data)
    {
      int i = 0;
      if (value.QueryIntValue(&i) == tinyxml2::XMLError::XML_SUCCESS)
      {
        data.emplace<int>(i);
        return true;
      }

      ASSERT_FAIL();
      return false;
    }
  }
}