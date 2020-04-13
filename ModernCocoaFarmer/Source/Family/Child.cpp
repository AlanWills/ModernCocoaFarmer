#include "Family/Child.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Stats/Modifier.h"


namespace MCF::Family
{
  REGISTER_SCRIPTABLE_OBJECT(Child);

  //------------------------------------------------------------------------------------------------
  const float STAT_MAX_VALUE = 100.0f;
  const char* const Child::HEALTH_FIELD_NAME = "health";
  const char* const Child::SAFETY_FIELD_NAME = "safety";
  const char* const Child::EDUCATION_FIELD_NAME = "education";
  const char* const Child::HAPPINESS_FIELD_NAME = "happiness";

  //------------------------------------------------------------------------------------------------
  Child::Child() :
    m_health(createValueField<float>(HEALTH_FIELD_NAME, STAT_MAX_VALUE)),
    m_safety(createValueField<float>(SAFETY_FIELD_NAME, STAT_MAX_VALUE)),
    m_education(createValueField<float>(EDUCATION_FIELD_NAME, 0)),
    m_happiness(createValueField<float>(HAPPINESS_FIELD_NAME, STAT_MAX_VALUE)),
    m_currentLocation(),
    m_isSelected(false)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyHealthModifier(const Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_health);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applySafetyModifier(const Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_safety);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyEducationModifier(const Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_education);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyHappinessModifier(const Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_happiness);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyModifier(const Stats::Modifier& modifier, Celeste::ValueField<float>& attributeToModify)
  {
    if (modifier.getChangeType() == Stats::ChangeType::kAbsolute)
    {
      attributeToModify.setValue(static_cast<float>(modifier.getAmount()));
    }
    else if (modifier.getChangeType() == Stats::ChangeType::kDelta)
    {
      attributeToModify.setValue(attributeToModify.getValue() + static_cast<float>(modifier.getAmount()));
    }
    else
    {
      ASSERT_FAIL();
    }

    attributeToModify.setValue(std::min(attributeToModify.getValue(), STAT_MAX_VALUE));
  }
}