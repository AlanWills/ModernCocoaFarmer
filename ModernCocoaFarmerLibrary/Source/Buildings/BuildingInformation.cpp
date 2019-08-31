#include "Buildings/BuildingInformation.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF
{
  namespace Buildings
  {
    REGISTER_SCRIPTABLE_OBJECT(BuildingInformation);

    //------------------------------------------------------------------------------------------------
    const std::string BuildingInformation::DESCRIPTION_FIELD_NAME = "description";

    //------------------------------------------------------------------------------------------------
    BuildingInformation::BuildingInformation() :
      m_description(createReferenceField<std::string>(DESCRIPTION_FIELD_NAME))
    {
    }
  }
}