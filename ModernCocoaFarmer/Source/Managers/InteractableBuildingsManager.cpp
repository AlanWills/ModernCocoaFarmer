#include "Managers/InteractableBuildingsManager.h"
#include "Screens/Screen.h"
#include "Input/MouseInteractionHandler.h"
#include "UI/InteractableBuildingDialog.h"

using namespace CelesteEngine;
using namespace CelesteEngine::Input;


namespace MCF
{
  namespace Managers
  {
    //------------------------------------------------------------------------------------------------
    InteractableBuildingsManager::InteractableBuildingsManager() :
      m_buildings()
    {
    }

    //------------------------------------------------------------------------------------------------
    void InteractableBuildingsManager::initialize(const Handle<Screen>& screen)
    {
      Handle<GameObject> interactableBuildings = screen->findGameObject("InteractableBuildings");
      ASSERT(!interactableBuildings.is_null());

      for (size_t childIndex = 0, childCount = interactableBuildings->getChildCount(); childIndex < childCount; ++childIndex)
      {
        Handle<GameObject> interactableBuilding = interactableBuildings->getChildGameObject(childIndex);
        interactableBuilding->findChildGameObject("Icon")->findComponent<MouseInteractionHandler>()->getOnLeftButtonClickedEvent().subscribe(
          [&](EventArgs& e, Handle<GameObject> caller) -> void
          {
            UI::showInteractableBuildingDialog(screen);
          });

        m_buildings.push_back(interactableBuilding);
      }
    }
  }
}