#include "Data/ObjectRef.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  ObjectRef::ObjectRef(DataSystem& dataSystem, const std::string& key) :
    m_dataSystem(dataSystem),
    m_key(key)
  {
  }

  //------------------------------------------------------------------------------------------------
  std::string ObjectRef::createFormattedElementKey(const std::string& elementKey) const
  {
    std::string key(m_key);
    key.push_back('.');
    key.append(elementKey);

    return key;
  }
}