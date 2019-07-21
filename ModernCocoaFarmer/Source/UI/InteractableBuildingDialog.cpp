#include "UI/InteractableBuildingDialog.h"
#include "Resources/ResourceManager.h"
#include "Input/MouseInteractionHandler.h"
#include "Screens/Screen.h"
#include "Physics/Collider.h"

using namespace CelesteEngine;
using namespace CelesteEngine::Resources;
using namespace CelesteEngine::Input;


namespace MCF
{
  namespace UI
  {
    Handle<GameObject> showInteractableBuildingDialog(const CelesteEngine::Handle<CelesteEngine::Screen>& screen)
    {
      // MOVE ALL OF THIS TO INTERACTABLE BUILDINGS MANAGER SO WE CAN SET UP THE PREFAB FIRST

      Handle<GameObject> gameObject = screen->findGameObject("InteractableBuildingPopup");
      gameObject->setActive(true);
      gameObject->setShouldRender(true);

      static bool initialized = false;

      if (!initialized)
      {
        // Set up close button disabling popup
        gameObject->getChildGameObject(0)->findComponent<MouseInteractionHandler>()->getOnLeftButtonClickedEvent().subscribe(
          [&](EventArgs& e, Handle<GameObject> caller) -> void
          {
            caller->getParent()->setActive(false);
            caller->getParent()->setShouldRender(false);

            // This is a hack because without killing the prefab or unsubscribing from the event
            // we need to reset the collider so that this callback is not instantly called when we next left click
            caller->findComponent<Physics::Collider>()->setHitByRay(false);
          });

        initialized = true;
      }

      return gameObject;
    }
  }
}