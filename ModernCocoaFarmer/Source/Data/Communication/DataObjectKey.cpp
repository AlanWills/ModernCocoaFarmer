#include "Data/Communication/DataObjectKey.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Communication
{
  REGISTER_COMPONENT(DataObjectKey, 10);

  //------------------------------------------------------------------------------------------------
  const std::string DataObjectKey::ROOT_KEY_PORT_NAME("root_key");

  //------------------------------------------------------------------------------------------------
  DataObjectKey::DataObjectKey(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_rootKeyPort(createInputPort<std::string>(ROOT_KEY_PORT_NAME, [this](Persistence::Data&& newValue) { onRootKeyPortChanged(std::move(newValue)); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  std::string createFullKey(const std::string& rootPath, const std::string& subPath)
  {
    std::string fullKey(rootPath);
    fullKey.push_back('.');
    fullKey.append(subPath);

    return fullKey;
  }

  //------------------------------------------------------------------------------------------------
  void DataObjectKey::addSubKey(const std::string& subPath)
  {
    auto subKeyPortIt = m_subKeyPorts.find(subPath);
    ASSERT(subKeyPortIt == m_subKeyPorts.end());

    if (subKeyPortIt == m_subKeyPorts.end())
    {
      m_subKeyPorts.emplace(subPath, createOutputPort<std::string>(subPath));
    }
  }

  //------------------------------------------------------------------------------------------------
  void DataObjectKey::onRootKeyPortChanged(Persistence::Data&& newValue)
  {
    for (auto& subKeyPort : m_subKeyPorts)
    {
      subKeyPort.second.get().setValue(createFullKey(std::get<std::string>(newValue), subKeyPort.first));
    }
  }
}