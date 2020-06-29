#include "Locations/Location.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Family/Child.h"
#include "Utils/LocaTokens.h"

using namespace Celeste::XML;


namespace MCF::Locations
{
  REGISTER_SCRIPTABLE_OBJECT(Location);

  //------------------------------------------------------------------------------------------------
  const std::string Location::DESCRIPTION_FIELD_NAME = "description";
  const std::string Location::ICON_FIELD_NAME = "icon";
  const std::string Location::SFX_FIELD_NAME = "sfx";
  const std::string Location::HEALTH_MODIFIER_FIELD_NAME = "HealthModifier";
  const std::string Location::SAFETY_MODIFIER_FIELD_NAME = "SafetyModifier";
  const std::string Location::EDUCATION_MODIFIER_FIELD_NAME = "EducationModifier";
  const std::string Location::HAPPINESS_MODIFIER_FIELD_NAME = "HappinessModifier";
  const std::string Location::MONEY_MODIFIER_FIELD_NAME = "MoneyModifier";
  const std::string Location::DAYS_TO_COMPLETE_FIELD_NAME = "days_to_complete";

  //------------------------------------------------------------------------------------------------
  Location::Location() :
    m_description(createReferenceField<std::string>(DESCRIPTION_FIELD_NAME)),
    m_icon(createReferenceField<std::string>(ICON_FIELD_NAME)),
    m_sfx(createReferenceField<std::string>(SFX_FIELD_NAME)),
    m_healthModifier(createScriptableObject<Stats::Modifier>(HEALTH_MODIFIER_FIELD_NAME)),
    m_safetyModifier(createScriptableObject<Stats::Modifier>(SAFETY_MODIFIER_FIELD_NAME)),
    m_educationModifier(createScriptableObject<Stats::Modifier>(EDUCATION_MODIFIER_FIELD_NAME)),
    m_happinessModifier(createScriptableObject<Stats::Modifier>(HAPPINESS_MODIFIER_FIELD_NAME)),
    m_moneyModifier(createScriptableObject<Stats::Modifier>(MONEY_MODIFIER_FIELD_NAME)),
    m_daysToComplete(createValueField<unsigned int>(DAYS_TO_COMPLETE_FIELD_NAME, 1U)),
    m_onChildSentEvent(),
    m_onChildLeftEvent()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Location::doDeserialize(const tinyxml2::XMLElement* /*element*/)
  {
    bool result = true;

    float daysToCompleteNormalizer = static_cast<float>(getDaysToComplete());
    m_healthModifier.setNormalizer(daysToCompleteNormalizer);
    m_safetyModifier.setNormalizer(daysToCompleteNormalizer);
    m_educationModifier.setNormalizer(daysToCompleteNormalizer);
    m_happinessModifier.setNormalizer(daysToCompleteNormalizer);

    return result;
  }

  //------------------------------------------------------------------------------------------------
  void Location::sendChild(Family::Child& child)
  {
    child.setCurrentLocation(getName());
    child.setTimeAtLocation(0);
    m_onChildSentEvent.invoke(child);
  }

  //------------------------------------------------------------------------------------------------
  void Location::leaveChild(Family::Child& child)
  {
    child.setCurrentLocation("");
    child.setTimeAtLocation(0);
    m_onChildLeftEvent.invoke(child);
  }

  //------------------------------------------------------------------------------------------------
  void Location::applyModifiers(Family::Child& child)
  {
    child.applyHealthModifier(m_healthModifier);
    child.applySafetyModifier(m_safetyModifier);
    child.applyEducationModifier(m_educationModifier);
    child.applyHappinessModifier(m_happinessModifier);
  }
}