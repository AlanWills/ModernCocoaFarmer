#include "Lua/ScriptCommands/Buildings/BuildingManagerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Buildings/BuildingsManager.h"
#include "Buildings/Building.h"
#include "Family/Child.h"


namespace MCF::Lua::Buildings::BuildingManagerScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using BuildingsManager = MCF::Buildings::BuildingsManager;

    CelesteEngine::Lua::registerScriptableObjectUserType<BuildingsManager>(
      BuildingsManager::type_name(),
      sol::base_classes, sol::bases<CelesteEngine::ScriptableObject>(),
      "getNumBuildings", &BuildingsManager::getNumBuildings,
      "getBuilding", &BuildingsManager::getBuilding,
      "setTimeManager", &BuildingsManager::setTimeManager);
  }
}