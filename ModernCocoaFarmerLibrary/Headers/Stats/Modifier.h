#pragma once

#include "Objects/ScriptableObject.h"
#include "MCFLibraryDllExport.h"
#include "ModifierEnums.h"
#include "Bindings/Stats/ModifierEnumsDataBindingGenerators.h"
#include "Deserialization/Stats/ModifierEnumsDeserializers.h"


namespace MCF
{
  namespace Stats
  {
    class MCFLibraryDllExport Modifier : public CelesteEngine::ScriptableObject
    {
      DECLARE_SCRIPTABLE_OBJECT(Modifier);

      public:
        int getAmount() const { return m_amount.getValue(); }
        ChangeType getChangeType() const { return m_changeType.getValue(); }
        Occurrence getOccurrence() const { return m_occurrence.getValue(); }
        int getPeriodInMonths() const { return m_periodInMonths.getValue(); }

        static const std::string AMOUNT_FIELD_NAME;
        static const std::string CHANGE_TYPE_FIELD_NAME;
        static const std::string OCCURRENCE_FIELD_NAME;
        static const std::string PERIOD_IN_MONTHS_FIELD_NAME;

      private:
        CelesteEngine::ValueField<int>& m_amount;
        CelesteEngine::ValueField<ChangeType>& m_changeType;
        CelesteEngine::ValueField<Occurrence>& m_occurrence;
        CelesteEngine::ValueField<int>& m_periodInMonths;
    };
  }
}