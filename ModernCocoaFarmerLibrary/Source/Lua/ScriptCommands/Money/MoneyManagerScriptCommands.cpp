#include "Lua/ScriptCommands/Money/MoneyManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "Money/MoneyManager.h"
#include "Stats/Modifier.h"

using namespace MCF::Money;


namespace MCF::Lua::Money::MoneyManagerScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    Celeste::Lua::registerScriptableObjectUserType<MoneyManager>(
      MoneyManager::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "getMoney", &MoneyManager::getMoney,
      "setMoney", &MoneyManager::setMoney,
      "applyMoneyModifier", &MoneyManager::applyMoneyModifier);
  }
}