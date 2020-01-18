#include "Buildings/Building.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/Child.h"


namespace MCF::Buildings
{
  REGISTER_SCRIPTABLE_OBJECT(Building);

  //------------------------------------------------------------------------------------------------
  const std::string Building::PREFAB_FIELD_NAME = "prefab";
  const std::string Building::DESCRIPTION_FIELD_NAME = "description";
  const std::string Building::HEALTH_MODIFIER_FIELD_NAME = "HealthModifier";
  const std::string Building::SAFETY_MODIFIER_FIELD_NAME = "SafetyModifier";
  const std::string Building::EDUCATION_MODIFIER_FIELD_NAME = "EducationModifier";
  const std::string Building::HAPPINESS_MODIFIER_FIELD_NAME = "HappinessModifier";
  const std::string Building::MONEY_MODIFIER_FIELD_NAME = "MoneyModifier";
  const std::string Building::MONTHS_TO_COMPLETE_FIELD_NAME = "months_to_complete";

  //------------------------------------------------------------------------------------------------
  Building::Building() :
    m_prefab(createReferenceField<std::string>(PREFAB_FIELD_NAME)),
    m_description(createReferenceField<std::string>(DESCRIPTION_FIELD_NAME)),
    m_healthModifier(createScriptableObject<Stats::ChildModifier>(HEALTH_MODIFIER_FIELD_NAME)),
    m_safetyModifier(createScriptableObject<Stats::ChildModifier>(SAFETY_MODIFIER_FIELD_NAME)),
    m_educationModifier(createScriptableObject<Stats::ChildModifier>(EDUCATION_MODIFIER_FIELD_NAME)),
    m_happinessModifier(createScriptableObject<Stats::ChildModifier>(HAPPINESS_MODIFIER_FIELD_NAME)),
    m_moneyModifier(createScriptableObject<Stats::Modifier>(MONEY_MODIFIER_FIELD_NAME)),
    m_monthsToComplete(createValueField<float>(MONTHS_TO_COMPLETE_FIELD_NAME)),
    m_children()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Building::sendChild(Family::Child& child)
  {
    m_children.push_back(child);
    child.setCurrentBuilding(getName());
  }

  //------------------------------------------------------------------------------------------------
  void Building::updateCurrentChildren()
  {
    for (const std::reference_wrapper<Family::Child>& child : m_children)
    {
      child.get().applyHealthModifier(m_healthModifier);
      child.get().applySafetyModifier(m_safetyModifier);
      child.get().applyEducationModifier(m_educationModifier);
      child.get().applyHappinessModifier(m_happinessModifier);
    }
  }
}