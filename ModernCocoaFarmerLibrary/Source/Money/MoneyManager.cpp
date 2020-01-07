#include "Money/MoneyManager.h"
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
    m_salaryLevel(createValueField<unsigned int>(SALARY_LEVEL_ATTRIBUTE_NAME, 1)),
    m_onMoneyChanged()
  {
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::setMoney(int money)
  {
    m_money.setValue(money);
    m_onMoneyChanged.invoke(money);
  }

  //------------------------------------------------------------------------------------------------
  void MoneyManager::applyMoneyModifier(Stats::Modifier& modifier)
  {
    if (modifier.getOccurrence() == Stats::Occurrence::kInstant)
    {
      if (modifier.getChangeType() == Stats::ChangeType::kAbsolute)
      {
        m_money.setValue(modifier.getAmount());
      }
      else if (modifier.getChangeType() == Stats::ChangeType::kDelta)
      {
        m_money.setValue(m_money.getValue() + modifier.getAmount());
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
}