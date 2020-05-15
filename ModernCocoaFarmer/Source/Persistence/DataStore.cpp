#include "Persistence/DataStore.h"
#include "Assert/Assert.h"
#include "XML/ChildXMLElementWalker.h"


namespace MCF::Persistence
{
  const char* const DataStore::DATA_TYPE_ATTRIBUTE_NAME = "data_type";
  const char* const DataStore::KEY_ATTRIBUTE_NAME = "key";
  const char* const DataStore::VALUE_ATTRIBUTE_NAME = "value";

  //------------------------------------------------------------------------------------------------
  using SerializeFunctions = celstl::VariantFunctions<DataStore::Data, void, tinyxml2::XMLElement&, const DataStore::Data&>;
  using DeserializeFunctions = celstl::VariantFunctions<DataStore::Data, bool, const tinyxml2::XMLAttribute&, DataStore::Data&>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct SerializeFunctor
  {
    static void execute(tinyxml2::XMLElement& element, const DataStore::Data& data)
    {
      element.SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, std::get<T>(data));
    }
  };

  //------------------------------------------------------------------------------------------------
  template <>
  struct SerializeFunctor<std::string>
  {
    static void execute(tinyxml2::XMLElement& element, const DataStore::Data& data)
    {
      element.SetAttribute(DataStore::VALUE_ATTRIBUTE_NAME, std::get<std::string>(data).c_str());
    }
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct DeserializeFunctor
  {
    static bool execute(const tinyxml2::XMLAttribute& attribute, DataStore::Data& data)
    {
      T t;
      if (Celeste::XML::getAttributeData(&attribute, t) == Celeste::XML::XMLValueError::kSuccess)
      {
        data.emplace<T>(t);
        return true;
      }

      ASSERT_FAIL();
      return false;
    }
  };
  
  static SerializeFunctions s_serializeFunctions = celstl::createVariantFunctions<SerializeFunctions, SerializeFunctor>();
  static DeserializeFunctions s_deserializeFunctions = celstl::createVariantFunctions<DeserializeFunctions, DeserializeFunctor>();

  //------------------------------------------------------------------------------------------------
  DataStore::DataStore() :
    DataStore(DataLookup())
  {
  }

  //------------------------------------------------------------------------------------------------
  DataStore::DataStore(DataLookup&& data) :
    m_dataLookup(std::move(data))
  {
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

      size_t typeIndex = dataPair.second.index();

      element->SetAttribute(KEY_ATTRIBUTE_NAME, dataPair.first.c_str());
      element->SetAttribute(DATA_TYPE_ATTRIBUTE_NAME, static_cast<unsigned int>(typeIndex));

      if (typeIndex < std::variant_size<DataStore::Data>())
      {
        s_serializeFunctions.m_functions[typeIndex](*element, dataPair.second);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  DataStore DataStore::deserialize(const tinyxml2::XMLElement& dataElementRoot)
  {
    DataLookup dataLookup;

    for (const auto& element : Celeste::XML::children(&dataElementRoot))
    {
      size_t dataType = static_cast<size_t>(element->UnsignedAttribute(DATA_TYPE_ATTRIBUTE_NAME, static_cast<unsigned int>(s_deserializeFunctions.size())));
      bool deserializeFuncExists = dataType < s_deserializeFunctions.size();

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
          s_deserializeFunctions.m_functions[dataType](*valueAttr, data))
        {
          dataLookup.insert(std::make_pair(key, data));
        }
      }
    }

    return DataStore(std::move(dataLookup));
  }
}