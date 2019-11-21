#include "Family/ChildInformation.h"


namespace MCF::Family
{
  const char* const ChildInformation::HEALTH_FIELD_NAME = "health";
  const char* const ChildInformation::SAFETY_FIELD_NAME = "safety";
  const char* const ChildInformation::EDUCATION_FIELD_NAME = "education";
  const char* const ChildInformation::HAPPINESS_FIELD_NAME = "happiness";

  //------------------------------------------------------------------------------------------------
  ChildInformation::ChildInformation() :
    m_health(createValueField<float>(HEALTH_FIELD_NAME, 100)),
    m_safety(createValueField<float>(SAFETY_FIELD_NAME, 100)),
    m_education(createValueField<float>(EDUCATION_FIELD_NAME, 0)),
    m_happiness(createValueField<float>(HAPPINESS_FIELD_NAME, 100))
  {
  }
}