#include "Data/Resources/ResourceDictionary.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Rendering/SpriteRenderer.h"


namespace MCF::Data::Resources
{
  REGISTER_COMPONENT(ResourceDictionary, 10);

  //------------------------------------------------------------------------------------------------
  const std::string ResourceDictionary::KEY_PORT_NAME("key");

  //------------------------------------------------------------------------------------------------
  ResourceDictionary::ResourceDictionary(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_key(createInputPort<std::string>(KEY_PORT_NAME, [this](Persistence::Data&& newValue) { onKeyChanged(std::move(newValue)); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ResourceDictionary::addResourceOption(const std::string& key, const Celeste::Path& resourcePath)
  {
    ASSERT(m_resourceLookup.find(key) == m_resourceLookup.end());
    if (m_resourceLookup.find(key) == m_resourceLookup.end())
    {
      m_resourceLookup.emplace(key, resourcePath);
    }
  }

  //------------------------------------------------------------------------------------------------
  void ResourceDictionary::setResourceOptions(const std::unordered_map<std::string, Celeste::Path>& resourceOptions)
  {
    m_resourceLookup = resourceOptions;
  }

  //------------------------------------------------------------------------------------------------
  void ResourceDictionary::onKeyChanged(Persistence::Data&& newValue)
  {
    std::string key = std::get<std::string>(newValue);
    
    switch (m_resourceType)
    {
    case ResourceType::kTexture:
    {
      setTexture(key);
      break;
    }
    default:
      break;
    }
  }

  //------------------------------------------------------------------------------------------------
  void ResourceDictionary::setTexture(const std::string& key)
  {
    auto spriteRenderer = getGameObject().findComponent<Celeste::Rendering::SpriteRenderer>();
    if (spriteRenderer != nullptr)
    {
      if (m_resourceLookup.find(key) != m_resourceLookup.end())
      {
        spriteRenderer->setTexture(m_resourceLookup.at(key));
      }
      else
      {
        spriteRenderer->setTexture(nullptr);
      }
    }
  }
}