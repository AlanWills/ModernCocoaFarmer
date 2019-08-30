#include "Buildings/Building.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF
{
  namespace Buildings
  {
    REGISTER_SCRIPTABLE_OBJECT(Building);

    //------------------------------------------------------------------------------------------------
    const std::string Building::DESCRIPTION_FIELD_NAME = "description";

    //------------------------------------------------------------------------------------------------
    Building::Building() :
      m_description(createReferenceField<std::string>(DESCRIPTION_FIELD_NAME))
    {
    }
  }
}