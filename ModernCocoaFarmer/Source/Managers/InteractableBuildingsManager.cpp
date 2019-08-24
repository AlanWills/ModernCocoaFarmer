#include "Managers/InteractableBuildingsManager.h"
#include "Screens/Screen.h"
#include "Input/MouseInteractionHandler.h"
#include "UI/InteractableBuildingDialog.h"
#include "Screens/ScreenUtils.h"

using namespace CelesteEngine;
using namespace CelesteEngine::Input;


namespace MCF
{
  namespace Managers
  {
    const std::string InteractableBuildingsManager::INTERACTABLE_BUILDINGS = "InteractableBuildings";

    //------------------------------------------------------------------------------------------------
    InteractableBuildingsManager::InteractableBuildingsManager() :
      m_buildings(),
      m_interactableBuildingDialog()
    {
    }

    //------------------------------------------------------------------------------------------------
    void InteractableBuildingsManager::initialize(const CelesteEngine::Handle<CelesteEngine::Screen>& screen)
    {
      m_interactableBuildingDialog = screen->findGameObject(UI::InteractableBuildingDialog::INTERACTABLE_BUILDING_DIALOG);

      // Set up close button disabling popup
      m_interactableBuildingDialog->getChildGameObject(0)->findComponent<MouseInteractionHandler>()->getOnLeftButtonClickedEvent().subscribe(
        [&](EventArgs& e, Handle<GameObject> caller) -> void
        {
          caller->getParent()->setActive(false);
          caller->getParent()->setShouldRender(false);

          // This is a hack because without killing the prefab or unsubscribing from the event
          // we need to reset the collider so that this callback is not instantly called when we next left click
          caller->findComponent<Physics::Collider>()->setHitByRay(false);
        });

      Handle<GameObject> interactableBuildings = screen->findGameObject(INTERACTABLE_BUILDINGS);
      ASSERT(!interactableBuildings.is_null());

      for (size_t childIndex = 0, childCount = interactableBuildings->getChildCount(); childIndex < childCount; ++childIndex)
      {
        Handle<GameObject> interactableBuilding = interactableBuildings->getChildGameObject(childIndex);
        interactableBuilding->findChildGameObject("Icon")->findComponent<MouseInteractionHandler>()->getOnLeftButtonClickedEvent().subscribe(
          [&](EventArgs& e, Handle<GameObject> caller) -> void
          {
            m_interactableBuildingDialog->getTransform()->setTranslation(getViewportDimensions() * 0.5f);
            m_interactableBuildingDialog->setActive(true);
            m_interactableBuildingDialog->setShouldRender(true);
          });

        m_buildings.push_back(interactableBuilding);
      }
    }
  }
}