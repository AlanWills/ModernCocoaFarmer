#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"


namespace MCF::Family
{
  class ChildInformation : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(ChildInformation, MCFLibraryDllExport)

    public:
      float getHealth() const { return m_health.getValue(); }
      void setHealth(float health) const { return m_health.setValue(health); }

      float getSafety() const { return m_safety.getValue(); }
      float getEducation() const { return m_education.getValue(); }
      float getHappiness() const { return m_happiness.getValue(); }

      static const char* const HEALTH_FIELD_NAME;
      static const char* const SAFETY_FIELD_NAME;
      static const char* const EDUCATION_FIELD_NAME;
      static const char* const HAPPINESS_FIELD_NAME;

    private:
      CelesteEngine::ValueField<float>& m_health;
      CelesteEngine::ValueField<float>& m_safety;
      CelesteEngine::ValueField<float>& m_education;
      CelesteEngine::ValueField<float>& m_happiness;
  };
}