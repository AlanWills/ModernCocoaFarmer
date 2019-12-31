#include "Lua/ScriptCommands/Money/MoneyManagerScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "Money/MoneyManager.h"
#include "Stats/Modifier.h"

using namespace MCF::Money;


namespace MCF::Lua::Money::MoneyManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void subscribeOnMoneyChangedCallback(
      MoneyManager& moneyManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<MoneyManager::MoneyChangedEvent, int>(moneyManager.getOnMoneyChangedEvent(), callback, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CelesteEngine::Lua::registerScriptableObjectUserType<MoneyManager>(
      MoneyManager::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "getMoney", &MoneyManager::getMoney,
      "setMoney", &MoneyManager::setMoney,
      "applyMoneyModifier", &MoneyManager::applyMoneyModifier,
      "subscribeOnMoneyChangedCallback", &Internals::subscribeOnMoneyChangedCallback);
  }
}