#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "ModifierEnums.h"
#include "Deserialization/Stats/ModifierEnumsDeserializers.h"


namespace MCF::Stats
{
  class Modifier : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(Modifier, MCFLibraryDllExport);

    public:
      float getAmount() const { return m_amount.getValue(); }
      void setAmount(float amount) { m_amount.setValue(amount); }

      ChangeType getChangeType() const { return m_changeType.getValue(); }
      void setChangeType(ChangeType changeType) { m_changeType.setValue(changeType); }

      float getNormalizer() const { return m_normalizer; }
      void setNormalizer(float normalizer) { m_normalizer = normalizer; }

      float getNormalizedAmount() const { return getAmount() / m_normalizer; }

      static const char* const AMOUNT_FIELD_NAME;
      static const char* const CHANGE_TYPE_FIELD_NAME;

    private:
      Celeste::ValueField<float>& m_amount;
      Celeste::ValueField<ChangeType>& m_changeType;

      float m_normalizer = 1;
  };
}