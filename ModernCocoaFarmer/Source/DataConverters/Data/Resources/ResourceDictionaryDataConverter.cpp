#include "DataConverters/Data/Resources/ResourceDictionaryDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Resources/ResourceDictionary.h"


namespace MCF::DataConverters::Data::Resources
{
  REGISTER_COMPONENT_DATA_CONVERTER(ResourceDictionaryDataConverter);

  //------------------------------------------------------------------------------------------------
  const char* const ResourceDictionaryDataConverter::RESOURCE_TYPE_ATTRIBUTE_NAME("type");
  const char* const ResourceDictionaryDataConverter::RESOURCE_ELEMENT_NAME("Resource");
  const char* const ResourceDictionaryDataConverter::KEY_ATTRIBUTE_NAME("key");
  const char* const ResourceDictionaryDataConverter::PATH_ATTRIBUTE_NAME("path");

  //------------------------------------------------------------------------------------------------
  ResourceDictionaryDataConverter::ResourceDictionaryDataConverter() :
    Inherited(MCF::Data::Resources::ResourceDictionary::type_name()),
    m_resourceType(createValueAttribute<size_t>(RESOURCE_TYPE_ATTRIBUTE_NAME, 0, Celeste::DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool ResourceDictionaryDataConverter::doConvertFromXML(const tinyxml2::XMLElement* element)
  {
    for (const tinyxml2::XMLElement* resource : Celeste::XML::children(element, RESOURCE_ELEMENT_NAME))
    {
      std::string key;
      if (Celeste::XML::getAttributeData(resource, KEY_ATTRIBUTE_NAME, key) != Celeste::XML::XMLValueError::kSuccess)
      {
        ASSERT_FAIL();
        return false;
      }

      std::string path;
      if (Celeste::XML::getAttributeData(resource, PATH_ATTRIBUTE_NAME, path) != Celeste::XML::XMLValueError::kSuccess)
      {
        ASSERT_FAIL();
        return false;
      }

      if (m_resources.find(key) != m_resources.end())
      {
        ASSERT_FAIL();
        return false;
      }

      m_resources.emplace(key, Celeste::Path(path));
    }

    return Inherited::doConvertFromXML(element);
  }

  //------------------------------------------------------------------------------------------------
  void ResourceDictionaryDataConverter::doSetValues(MCF::Data::Resources::ResourceDictionary& resourceDictionary) const
  {
    Inherited::doSetValues(resourceDictionary);

    resourceDictionary.setResourceType(getResourceType());
    resourceDictionary.setResourceOptions(getResources());
  }
}