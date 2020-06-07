#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"
#include "Data/Resources/ResourceType.h"
#include "FileSystem/Path.h"

#include <unordered_map>


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Resources
{
  class ResourceDictionary : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(ResourceDictionary, DataSystem, MCFLibraryDllExport);

    public:
      ResourceType getResourceType() const { return m_resourceType; }
      void setResourceType(ResourceType resourceType) { m_resourceType = resourceType; }

      void addResourceOption(const std::string& key, const Celeste::Path& resourcePath);
      void setResourceOptions(const std::unordered_map<std::string, Celeste::Path>& resourceOptions);

      static const std::string KEY_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onKeyChanged(Persistence::Data&& newValue);
      void setTexture(const std::string& key);

      InputPort& m_key;

      ResourceType m_resourceType = ResourceType::kTexture;
      std::unordered_map<std::string, Celeste::Path> m_resourceLookup;
  };
}