#include "Lua/ScriptCommands/UI/UIScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Screens/Screen.h"
#include "UI/InteractableBuildingDialog.h"
#include "Buildings/BuildingInformation.h"

using namespace CelesteEngine;
using namespace MCF::UI;


namespace MCF
{
  namespace Lua
  {
    namespace UIScriptCommands
    {
      //------------------------------------------------------------------------------------------------
      void initialize()
      {
        CelesteEngine::Lua::registerUserType<InteractableBuildingDialog>(
          "InteractableBuildingDialog",
          "show", &InteractableBuildingDialog::show);
      }
    }
  }
}