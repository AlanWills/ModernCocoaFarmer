#include "Lua/ScriptCommands/Events/GameEventManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Events/GameEventManager.h"
#include "Events/GameEvent.h"
#include "Time/TimeManager.h"
#include "Money/MoneyManager.h"
#include "Family/FamilyManager.h"
#include "Locations/LocationsManager.h"

using namespace MCF::Events;


namespace MCF::Lua::Events::GameEventManagerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void registerGameEvent(GameEventManager& gameEventManager, const std::string& prefabPath)
    {
      auto gameEvent = CelesteEngine::ScriptableObject::load<GameEvent>(prefabPath);
      ASSERT(gameEvent != nullptr);

      if (gameEvent != nullptr)
      {
        gameEventManager.registerGameEvent(std::unique_ptr<const GameEvent>(gameEvent.release()));
      }
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnGameEventTriggeredCallback(
      GameEventManager& gameEventManager,
      sol::protected_function callback,
      sol::object extraArgs)
    {
      CelesteEngine::Lua::subscribeToEvent<GameEventManager::GameEventTriggeredEvent, const GameEvent&>(
        gameEventManager.getGameEventTriggeredEvent(),
        callback,
        extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CelesteEngine::Lua::registerScriptableObjectUserType<GameEventManager>(
      GameEventManager::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "setFamilyManager", &GameEventManager::setFamilyManager,
      "setMoneyManager", &GameEventManager::setMoneyManager,
      "setTimeManager", &GameEventManager::setTimeManager,
      "setLocationsManager", &GameEventManager::setLocationsManager,
      "setNotificationManager", &GameEventManager::setNotificationManager,
      "registerGameEvent", &Internals::registerGameEvent,
      "subscribeOnGameEventTriggeredCallback", &Internals::subscribeOnGameEventTriggeredCallback);
  }
}