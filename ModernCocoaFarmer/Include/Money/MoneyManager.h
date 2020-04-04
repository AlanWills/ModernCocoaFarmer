#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Events/Event.h"


namespace MCF::Stats
{
  class Modifier;
}

namespace MCF::Persistence
{
  class DataStore;
}

namespace MCF::Money
{
  class MoneyManager : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(MoneyManager, MCFLibraryDllExport);

    public:
      using MoneyChangedEvent = Celeste::Event<int>;

      MCFLibraryDllExport void setDataStore(observer_ptr<Persistence::DataStore> dataStore);

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
      void updateDataStore() const;

      Celeste::ValueField<int>& m_money;
      Celeste::ValueField<unsigned int>& m_salaryLevel;

      observer_ptr<Persistence::DataStore> m_dataStore = nullptr;
  };
}