#include "Buildings/BuildingInformation.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF
{
  namespace Buildings
  {
    REGISTER_SCRIPTABLE_OBJECT(BuildingInformation);

    //------------------------------------------------------------------------------------------------
    const std::string BuildingInformation::DESCRIPTION_FIELD_NAME = "description";
    const std::string BuildingInformation::HEALTH_MODIFIER_FIELD_NAME = "HealthModifier";
    const std::string BuildingInformation::SAFETY_MODIFIER_FIELD_NAME = "SafetyModifier";
    const std::string BuildingInformation::EDUCATION_MODIFIER_FIELD_NAME = "EducationModifier";
    const std::string BuildingInformation::HAPPINESS_MODIFIER_FIELD_NAME = "HappinessModifier";
    const std::string BuildingInformation::MONEY_MODIFIER_FIELD_NAME = "MoneyModifier";
    const std::string BuildingInformation::MONTHS_TO_COMPLETE_FIELD_NAME = "months_to_complete";

    //------------------------------------------------------------------------------------------------
    BuildingInformation::BuildingInformation() :
      m_description(createReferenceField<std::string>(DESCRIPTION_FIELD_NAME)),
      m_healthModifier(createScriptableObject<Stats::Modifier>(HEALTH_MODIFIER_FIELD_NAME)),
      m_safetyModifier(createScriptableObject<Stats::Modifier>(SAFETY_MODIFIER_FIELD_NAME)),
      m_educationModifier(createScriptableObject<Stats::Modifier>(EDUCATION_MODIFIER_FIELD_NAME)),
      m_happinessModifier(createScriptableObject<Stats::Modifier>(HAPPINESS_MODIFIER_FIELD_NAME)),
      m_moneyModifier(createScriptableObject<Stats::Modifier>(MONEY_MODIFIER_FIELD_NAME)),
      m_monthsToComplete(createValueField<float>(MONTHS_TO_COMPLETE_FIELD_NAME))
    {
    }
  }
}