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
    class Modifier : public CelesteEngine::ScriptableObject
    {
      DECLARE_SCRIPTABLE_OBJECT(Modifier, MCFLibraryDllExport);

      public:
        int getAmount() const { return m_amount.getValue(); }
        ChangeType getChangeType() const { return m_changeType.getValue(); }
        Occurrence getOccurrence() const { return m_occurrence.getValue(); }
        int getPeriodInMonths() const { return m_periodInMonths.getValue(); }

        static const char* const AMOUNT_FIELD_NAME;
        static const char* const CHANGE_TYPE_FIELD_NAME;
        static const char* const OCCURRENCE_FIELD_NAME;
        static const char* const PERIOD_IN_MONTHS_FIELD_NAME;

      private:
        CelesteEngine::ValueField<int>& m_amount;
        CelesteEngine::ValueField<ChangeType>& m_changeType;
        CelesteEngine::ValueField<Occurrence>& m_occurrence;
        CelesteEngine::ValueField<int>& m_periodInMonths;
    };
  }
}