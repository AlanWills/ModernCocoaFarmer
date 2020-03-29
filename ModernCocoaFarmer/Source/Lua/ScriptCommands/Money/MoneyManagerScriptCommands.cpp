#include "Lua/ScriptCommands/Money/MoneyManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "Money/MoneyManager.h"
#include "Stats/Modifier.h"

using namespace MCF::Money;


namespace sol
{
  template <>
  struct is_to_stringable<MoneyManager> : std::false_type {};
}

namespace MCF::Lua::Money::MoneyManagerScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    Celeste::Lua::registerScriptableObjectUserType<MoneyManager>(
      MoneyManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "setDataStore", &MoneyManager::setDataStore,
      "getMoney", &MoneyManager::getMoney,
      "setMoney", &MoneyManager::setMoney,
      "applyMoneyModifier", &MoneyManager::applyMoneyModifier);
  }
}