#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Events/Event.h"


namespace MCF::Stats
{
  class Modifier;
}

namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Money
{
  class MoneyManager : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(MoneyManager, MCFLibraryDllExport);

    public:
      using MoneyChangedEvent = Celeste::Event<int>;

      MCFLibraryDllExport void setDataSystem(observer_ptr<Data::DataSystem> dataSystem);

      int getMoney() const { return m_money.getValue(); }
      MCFLibraryDllExport void setMoney(int money);

      unsigned int getSalaryLevel() const { return m_salaryLevel.getValue(); }
      MCFLibraryDllExport void setSalaryLevel(unsigned int salaryLevel);
      void incrementSalaryLevel() { setSalaryLevel(getSalaryLevel() + 1); }
      void decrementSalaryLevel() { if (getSalaryLevel() > 0) { setSalaryLevel(getSalaryLevel() - 1); } }

      MCFLibraryDllExport void applyMoneyModifier(const Stats::Modifier& modifier);

      static const char* const MONEY_ATTRIBUTE_NAME;
      static const char* const SALARY_LEVEL_ATTRIBUTE_NAME;

    private:
      void updateDataSystem() const;

      Celeste::ValueField<int>& m_money;
      Celeste::ValueField<unsigned int>& m_salaryLevel;

      observer_ptr<Data::DataSystem> m_dataSystem = nullptr;
  };
}