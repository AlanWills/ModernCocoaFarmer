#include "Buildings/BuildingInformation.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF
{
  namespace Buildings
  {
    REGISTER_SCRIPTABLE_OBJECT(BuildingInformation);

    //------------------------------------------------------------------------------------------------
    const std::string BuildingInformation::DESCRIPTION_FIELD_NAME = "description";
    const std::string BuildingInformation::HEALTH_MODIFIER_FIELD_NAME = "health_modifier";
    const std::string BuildingInformation::SAFETY_MODIFIER_FIELD_NAME = "safety_modifier";
    const std::string BuildingInformation::EDUCATION_MODIFIER_FIELD_NAME = "education_modifier";
    const std::string BuildingInformation::HAPPINESS_MODIFIER_FIELD_NAME = "happiness_modifier";
    const std::string BuildingInformation::COST_MODIFIER_FIELD_NAME = "cost_modifier";
    const std::string BuildingInformation::MONTHS_TO_COMPLETE_FIELD_NAME = "months_to_complete";

    //------------------------------------------------------------------------------------------------
    BuildingInformation::BuildingInformation() :
      m_description(createReferenceField<std::string>(DESCRIPTION_FIELD_NAME)),
      m_healthModifier(createReferenceField<Stats::Modifier>(HEALTH_MODIFIER_FIELD_NAME)),
      m_safetyModifier(createReferenceField<Stats::Modifier>(SAFETY_MODIFIER_FIELD_NAME)),
      m_educationModifier(createReferenceField<Stats::Modifier>(EDUCATION_MODIFIER_FIELD_NAME)),
      m_happinessModifier(createReferenceField<Stats::Modifier>(HAPPINESS_MODIFIER_FIELD_NAME)),
      m_costModifier(createReferenceField<Stats::Modifier>(COST_MODIFIER_FIELD_NAME)),
      m_monthsToComplete(createValueField<float>(MONTHS_TO_COMPLETE_FIELD_NAME))
    {
    }
  }
}