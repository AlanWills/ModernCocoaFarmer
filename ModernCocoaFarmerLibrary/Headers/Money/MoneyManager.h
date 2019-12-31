#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Events/Event.h"


namespace MCF::Stats
{
  class Modifier;
}

namespace MCF::Money
{
  class MoneyManager : public CelesteEngine::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(MoneyManager, MCFLibraryDllExport);

    public:
      using MoneyChangedEvent = CelesteEngine::Event<int>;

      int getMoney() const { return m_money.getValue(); }
      void setMoney(int money);

      void applyMoneyModifier(Stats::Modifier& modifier);

      const MoneyChangedEvent& getOnMoneyChangedEvent() const { return m_onMoneyChanged; }

      static const char* const MONEY_ATTRIBUTE_NAME;

    private:
      CelesteEngine::ValueField<int>& m_money;

      MoneyChangedEvent m_onMoneyChanged;
  };
}