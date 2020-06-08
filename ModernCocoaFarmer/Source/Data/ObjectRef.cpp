#include "Data/ObjectRef.h"
#include "Persistence/DataPath.h"


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
    return Persistence::DataPath::combine(m_key, elementKey);
  }
}