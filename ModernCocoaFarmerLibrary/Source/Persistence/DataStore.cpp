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

    DataStore::SerializeFunctions DataStore::m_serializeFunctions = DataStore::createSerializeFunctions();
    DataStore::DeserializeFunctions DataStore::m_deserializeFunctions = DataStore::createDeserializeFunctions();

    //------------------------------------------------------------------------------------------------
    DataStore::DataStore() :
      DataStore(DataLookup())
    {
    }

    //------------------------------------------------------------------------------------------------
    DataStore::DataStore(const std::unordered_map<std::string, Data>& data) :
      m_dataLookup(data)
    {
    }

    //------------------------------------------------------------------------------------------------
    DataStore::DataStore(DataStore&& rhs) noexcept :
      m_dataLookup(std::move(rhs.m_dataLookup))
    {
    }

    //------------------------------------------------------------------------------------------------
    constexpr DataStore::SerializeFunctions DataStore::createSerializeFunctions()
    {
      DataStore::SerializeFunctions serializeFunctions = DataStore::SerializeFunctions();
      setSerializeFunction<serializeFunctions.size() - 1>(serializeFunctions);

      return serializeFunctions;
    }

    //------------------------------------------------------------------------------------------------
    constexpr DataStore::DeserializeFunctions DataStore::createDeserializeFunctions()
    {
      DataStore::DeserializeFunctions deserializeFunctions = DataStore::DeserializeFunctions();
      setDeserializeFunction<deserializeFunctions.size() - 1>(deserializeFunctions);

      return deserializeFunctions;
    }

    //------------------------------------------------------------------------------------------------
    template <>
    static void DataStore::setSerializeFunction<0>(SerializeFunctions& serializeFunctions)
    {
      serializeFunctions.m_functions[0] = &DataStore::serialize<typename std::variant_alternative<0, Data>::type>;
    }

    //------------------------------------------------------------------------------------------------
    template <>
    static void DataStore::setDeserializeFunction<0>(DeserializeFunctions& deserializeFunctions)
    {
      deserializeFunctions.m_functions[0] = &DataStore::deserialize<typename std::variant_alternative<0, Data>::type>;
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

        size_t typeIndex = dataPair.second.index();

        element->SetAttribute(KEY_ATTRIBUTE_NAME, dataPair.first.c_str());
        element->SetAttribute(DATA_TYPE_ATTRIBUTE_NAME, static_cast<unsigned int>(typeIndex));
        
        if (typeIndex < std::variant_size<DataStore::Data>())
        {
          m_serializeFunctions.m_functions[typeIndex](*element, dataPair.second);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    DataStore DataStore::deserialize(const tinyxml2::XMLElement& dataElementRoot)
    {
      std::unordered_map<std::string, Data> dataLookup;

      for (const auto& element : CelesteEngine::XML::children(&dataElementRoot))
      {
        size_t dataType = static_cast<size_t>(element->UnsignedAttribute(DATA_TYPE_ATTRIBUTE_NAME, static_cast<unsigned int>(m_deserializeFunctions.size())));
        bool deserializeFuncExists = dataType < m_deserializeFunctions.size();

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
              m_deserializeFunctions.m_functions[dataType](*valueAttr, data))
          {
            dataLookup.insert(std::make_pair(key, data));
          }
        }
      }
      
      return DataStore(dataLookup);
    }
  }
}