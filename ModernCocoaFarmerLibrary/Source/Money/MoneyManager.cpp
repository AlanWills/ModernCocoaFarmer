#include "Money/MoneyManager.h"
#include "Money/DataSources.h"
#include "Persistence/DataStore.h"
#include "Stats/Modifier.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF::Money
{
  REGISTER_SCRIPTABLE_OBJECT(MoneyManager);

  //------------------------------------------------------------------------------------------------
  const char* const MoneyManager::MONEY_ATTRIBUTE_NAME = "money";
  const char* const MoneyManager::SALARY_LEVEL_ATTRIBUTE_NAME = "salary_level";

  //------------------------------------------------------------------------------------------------
  MoneyManager::MoneyManager() :
    m_money(createValueField<int>(MONEY_ATTRIBUTE_NAME, 100)),
    m_salaryLevel(createValueField<unsigned int>(SALARY_LEVEL_ATTRIBUTE_NAME, 1))
  {
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::setMoney(int money)
  {
    m_money.setValue(money);
    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::setSalaryLevel(unsigned int salaryLevel)
  {
    m_salaryLevel.setValue(salaryLevel);
    updateDataStore();
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::applyMoneyModifier(const Stats::Modifier& modifier)
  {
    if (modifier.getOccurrence() == Stats::Occurrence::kInstant)
    {
      if (modifier.getChangeType() == Stats::ChangeType::kAbsolute)
      {
        setMoney(static_cast<int>(modifier.getAmount()));
      }
      else if (modifier.getChangeType() == Stats::ChangeType::kDelta)
      {
        setMoney(m_money.getValue() + static_cast<int>(modifier.getAmount()));
      }
      else
      {
        ASSERT_FAIL();
      }
    }
    else if (modifier.getOccurrence() == Stats::Occurrence::kPeriodic)
    {
      ASSERT_FAIL_MSG("TODO");
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::updateDataStore() const
  {
    if (m_dataStore != nullptr)
    {
      m_dataStore->set(DataSources::CURRENT_MONEY, getMoney());
      m_dataStore->set(DataSources::CURRENT_SALARY_LEVEL, getSalaryLevel());
    }
  }
}