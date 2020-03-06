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
  class MoneyManager : public Celeste::ScriptableObject
  {
    DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(MoneyManager, MCFLibraryDllExport);

    public:
      using MoneyChangedEvent = Celeste::Event<int>;

      int getMoney() const { return m_money.getValue(); }
      void setMoney(int money);

      unsigned int getSalaryLevel() const { return m_salaryLevel.getValue(); }
      void setSalaryLevel(unsigned int salaryLevel) { m_salaryLevel.setValue(salaryLevel); }
      void incrementSalaryLevel() { setSalaryLevel(getSalaryLevel() + 1); }
      void decrementSalaryLevel() { if (getSalaryLevel() > 0) { setSalaryLevel(getSalaryLevel() - 1); } }

      void applyMoneyModifier(Stats::Modifier& modifier);

      static const char* const MONEY_ATTRIBUTE_NAME;
      static const char* const SALARY_LEVEL_ATTRIBUTE_NAME;

    private:
      Celeste::ValueField<int>& m_money;
      Celeste::ValueField<unsigned int>& m_salaryLevel;
  };
}