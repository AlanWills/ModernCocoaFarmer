#include "ScriptCommands/Money/MoneyManagerScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "Money/MoneyManager.h"
#include "Stats/Modifier.h"
#include "sol/sol.hpp"

using namespace MCF::Money;


namespace sol
{
  template <>
  struct is_to_stringable<MoneyManager> : std::false_type {};
}

namespace MCF::Lua::Money::MoneyManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void addMoney(MoneyManager& moneyManager, int amount)
    {
      moneyManager.setMoney(moneyManager.getMoney() + amount);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerScriptableObjectUserType<MoneyManager>(
      state,
      MoneyManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "setDataSystem", &MoneyManager::setDataSystem,
      "getMoney", &MoneyManager::getMoney,
      "setMoney", &MoneyManager::setMoney,
      "addMoney", &Internals::addMoney,
      "applyMoneyModifier", &MoneyManager::applyMoneyModifier,
      "getSalaryLevel", &MoneyManager::getSalaryLevel,
      "setSalaryLevel", &MoneyManager::setSalaryLevel,
      "incrementSalaryLevel", &MoneyManager::incrementSalaryLevel,
      "decrementSalaryLevel", &MoneyManager::decrementSalaryLevel);
  }
}