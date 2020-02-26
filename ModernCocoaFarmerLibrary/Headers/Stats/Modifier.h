#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "ModifierEnums.h"
#include "Bindings/Stats/ModifierEnumsDataBindingGenerators.h"
#include "Deserialization/Stats/ModifierEnumsDeserializers.h"


namespace MCF
{
  namespace Stats
  {
    class Modifier : public Celeste::ScriptableObject
    {
      DECLARE_SCRIPTABLE_OBJECT(Modifier, MCFLibraryDllExport);

      public:
        float getAmount() const { return m_amount.getValue(); }
        void setAmount(float amount) { m_amount.setValue(amount); }

        ChangeType getChangeType() const { return m_changeType.getValue(); }
        Occurrence getOccurrence() const { return m_occurrence.getValue(); }

        static const char* const AMOUNT_FIELD_NAME;
        static const char* const CHANGE_TYPE_FIELD_NAME;
        static const char* const OCCURRENCE_FIELD_NAME;

      private:
        Celeste::ValueField<float>& m_amount;
        Celeste::ValueField<ChangeType>& m_changeType;
        Celeste::ValueField<Occurrence>& m_occurrence;
    };
  }
}