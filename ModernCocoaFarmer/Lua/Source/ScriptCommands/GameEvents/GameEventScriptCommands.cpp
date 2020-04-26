#include "ScriptCommands/GameEvents/GameEventScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "GameEvents/GameEvent.h"
#include "GameEvents/Conditions/LuaCondition.h"
#include "GameEvents/Effects/LuaEffect.h"

using namespace Celeste;
using namespace MCF::GameEvents;


namespace sol
{
  template <>
  struct is_to_stringable<MCF::GameEvents::GameEvent> : std::false_type {};
}

namespace MCF::Lua::GameEvents::GameEventScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void addCondition_Instance(GameEvent& gameEvent, std::unique_ptr<Conditions::LuaCondition>& condition)
    {
      ASSERT(condition != nullptr);
      if (condition != nullptr)
      {
        gameEvent.addCondition(std::move(condition));
      }
    }

    //------------------------------------------------------------------------------------------------
    void addCondition_Path(GameEvent& gameEvent, const std::string& conditionPath)
    {
      std::unique_ptr<ScriptableObject> condition = ScriptableObject::load(conditionPath);

      ASSERT(condition != nullptr);
      if (condition != nullptr)
      {
        gameEvent.addCondition(std::move(std::unique_ptr<Conditions::Condition>(static_cast<Conditions::Condition*>(condition.release()))));
      }
    }

    //------------------------------------------------------------------------------------------------
    void addEffect_Instance(GameEvent& gameEvent, std::unique_ptr<Effects::LuaEffect>& effect)
    {
      ASSERT(effect != nullptr);
      if (effect != nullptr)
      {
        gameEvent.addEffect(std::move(effect));
      }
    }

    //------------------------------------------------------------------------------------------------
    void addEffect_Path(GameEvent& gameEvent, const std::string& effectPath)
    {
      std::unique_ptr<ScriptableObject> effect = ScriptableObject::load(effectPath);
      
      ASSERT(effect != nullptr);
      if (effect != nullptr)
      {
        gameEvent.addEffect(std::move(std::unique_ptr<Effects::Effect>(static_cast<Effects::Effect*>(effect.release()))));
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using GameEvent = MCF::GameEvents::GameEvent;

    Celeste::Lua::registerScriptableObjectUserType<GameEvent>(
      state,
      GameEvent::type_name(),
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "addCondition", sol::overload(&Internals::addCondition_Instance, &Internals::addCondition_Path),
      "addEffect", sol::overload(&Internals::addEffect_Instance, &Internals::addEffect_Path));
  }
}