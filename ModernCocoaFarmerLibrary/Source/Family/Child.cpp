#include "Family/Child.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Stats/Modifier.h"


namespace MCF::Family
{
  REGISTER_SCRIPTABLE_OBJECT(Child);

  //------------------------------------------------------------------------------------------------
  const char* const Child::HEALTH_FIELD_NAME = "health";
  const char* const Child::SAFETY_FIELD_NAME = "safety";
  const char* const Child::EDUCATION_FIELD_NAME = "education";
  const char* const Child::HAPPINESS_FIELD_NAME = "happiness";

  //------------------------------------------------------------------------------------------------
  Child::Child() :
    m_health(createValueField<float>(HEALTH_FIELD_NAME, 100)),
    m_safety(createValueField<float>(SAFETY_FIELD_NAME, 100)),
    m_education(createValueField<float>(EDUCATION_FIELD_NAME, 0)),
    m_happiness(createValueField<float>(HAPPINESS_FIELD_NAME, 100)),
    m_currentBuilding(),
    m_isSelected(false),
    m_onSelectedChanged()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Child::setSelected(bool isSelected)
  {
    if (m_isSelected == isSelected)
    {
      return;
    }

    m_isSelected = isSelected;
    m_onSelectedChanged.invoke(*this, m_isSelected);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyHealthModifier(Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_health);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applySafetyModifier(Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_safety);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyEducationModifier(Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_education);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyHappinessModifier(Stats::Modifier& modifier)
  {
    applyModifier(modifier, m_happiness);
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyModifier(Stats::Modifier& modifier, CelesteEngine::ValueField<float>& attributeToModify)
  {
    if (modifier.getOccurrence() == Stats::Occurrence::kInstant)
    {
      applyInstantModifier(modifier, attributeToModify);
    }
    else if (modifier.getOccurrence() == Stats::Occurrence::kPeriodic)
    {
      applyPeriodicModifier(modifier, attributeToModify);
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyInstantModifier(Stats::Modifier& modifier, CelesteEngine::ValueField<float>& attributeToModify)
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
  }

  //------------------------------------------------------------------------------------------------
  void Child::applyPeriodicModifier(Stats::Modifier& modifier, CelesteEngine::ValueField<float>& attributeToModify)
  {
    ASSERT_FAIL_MSG("TODO");
  }
}