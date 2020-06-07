#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"
#include "Data/Resources/ResourceType.h"

#include <unordered_map>


namespace MCF::Data::Resources
{
  class ResourceDictionary;
}

namespace MCF::DataConverters::Data::Resources
{
  class ResourceDictionaryDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(ResourceDictionaryDataConverter, MCF::Data::Resources::ResourceDictionary, MCFLibraryDllExport);

    public:
      MCF::Data::Resources::ResourceType getResourceType() const { return static_cast<MCF::Data::Resources::ResourceType>(m_resourceType.getValue()); }
      const std::unordered_map<std::string, Celeste::Path>& getResources() const { return m_resources; }

      static const char* const RESOURCE_TYPE_ATTRIBUTE_NAME;
      static const char* const RESOURCE_ELEMENT_NAME;
      static const char* const KEY_ATTRIBUTE_NAME;
      static const char* const PATH_ATTRIBUTE_NAME;

    protected:
      bool doConvertFromXML(const tinyxml2::XMLElement* element) override;

    private:
      using Inherited = DataNodeComponentDataConverter;

      Celeste::XML::ValueAttribute<size_t>& m_resourceType;

      std::unordered_map<std::string, Celeste::Path> m_resources;
  };
}