#include "Money/MoneyManager.h"
#include "Money/DataSources.h"
#include "Data/DataSystem.h"
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
    updateDataSystem();
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::setSalaryLevel(unsigned int salaryLevel)
  {
    m_salaryLevel.setValue(salaryLevel);
    updateDataSystem();
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::applyMoneyModifier(const Stats::Modifier& modifier)
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

  //------------------------------------------------------------------------------------------------
  void MoneyManager::setDataSystem(observer_ptr<Data::DataSystem> dataSystem)
  {
    m_dataSystem = dataSystem;
    updateDataSystem();
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::updateDataSystem() const
  {
    if (m_dataSystem != nullptr)
    {
      m_dataSystem->set(DataSources::CURRENT_MONEY, getMoney());
      m_dataSystem->set(DataSources::CURRENT_SALARY_LEVEL, getSalaryLevel());
    }
  }
}