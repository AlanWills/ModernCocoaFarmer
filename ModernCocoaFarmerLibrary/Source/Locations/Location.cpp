#include "Locations/Location.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/Child.h"


namespace MCF::Locations
{
  REGISTER_SCRIPTABLE_OBJECT(Location);

  //------------------------------------------------------------------------------------------------
  const std::string Location::PREFAB_FIELD_NAME = "prefab";
  const std::string Location::DESCRIPTION_FIELD_NAME = "description";
  const std::string Location::HEALTH_MODIFIER_FIELD_NAME = "HealthModifier";
  const std::string Location::SAFETY_MODIFIER_FIELD_NAME = "SafetyModifier";
  const std::string Location::EDUCATION_MODIFIER_FIELD_NAME = "EducationModifier";
  const std::string Location::HAPPINESS_MODIFIER_FIELD_NAME = "HappinessModifier";
  const std::string Location::MONEY_MODIFIER_FIELD_NAME = "MoneyModifier";
  const std::string Location::MONTHS_TO_COMPLETE_FIELD_NAME = "months_to_complete";

  //------------------------------------------------------------------------------------------------
  Location::Location() :
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
  void Location::sendChild(Family::Child& child)
  {
    m_children.push_back(child);
    child.setCurrentLocation(getName());
  }

  //------------------------------------------------------------------------------------------------
  void Location::updateCurrentChildren()
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