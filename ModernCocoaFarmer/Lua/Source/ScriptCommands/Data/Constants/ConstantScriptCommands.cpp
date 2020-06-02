#include "ScriptCommands/Data/Constants/ConstantScriptCommands.h"
#include "Data/Constants/Constant.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "sol/sol.hpp"

using Constant = MCF::Data::Constants::Constant;


namespace MCF::Lua::Data::ConstantScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerUserType<Constant>(
      state,
      Constant::type_name(),
      sol::base_classes, sol::bases<MCF::Data::DataNodeComponent, Celeste::Component, Celeste::Entity, Celeste::Object>(),
      "setValue", sol::overload(
        &Constant::setValue<bool>, 
        &Constant::setValue<int>, 
        &Constant::setValue<unsigned int>, 
        &Constant::setValue<std::string>,
        &Constant::setValue<glm::vec3>));
  }
}