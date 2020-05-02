#include "ScriptCommands/GameEvents/Effects/LuaEffectScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"

#include "GameEvents/Effects/LuaEffect.h"

namespace MCF::Lua::GameEvents::Effects::LuaEffectScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using namespace MCF::GameEvents::Effects;

    Celeste::Lua::registerScriptableObjectUserType<LuaEffect>(
      state,
      LuaEffect::type_name(),
      sol::base_classes, sol::bases<Effect, Celeste::ScriptableObject>(),
      "setTriggerFunc", &LuaEffect::setTriggerFunc);
  }
}