#include "UI/InteractableBuildingDialog.h"
#include "Screens/Screen.h"
#include "Input/MouseInteractionHandler.h"
#include "Resources/ResourceManager.h"
#include "Rendering/TextRenderer.h"
#include "Buildings/Building.h"
#include "ObjectFX/LimitedLifeTime.h"
#include "Resources/Data/Prefab.h"

using namespace CelesteEngine;
using namespace CelesteEngine::Input;
using namespace CelesteEngine::Resources;
using namespace CelesteEngine::Rendering;


namespace MCF
{
  namespace UI
  {
    //------------------------------------------------------------------------------------------------
    const std::string InteractableBuildingDialog::m_dialogPrefabPath = "Prefabs\\UI\\InteractableBuildingDialog.prefab";
    const std::string InteractableBuildingDialog::TITLE_TEXT_NAME = "TitleText";
    const std::string InteractableBuildingDialog::DESCRIPTION_TEXT_NAME = "DescriptionText";

    //------------------------------------------------------------------------------------------------
    InteractableBuildingDialog::InteractableBuildingDialog() :
      m_dialogPrefab()
    {
    }

    //------------------------------------------------------------------------------------------------
    void InteractableBuildingDialog::initialize()
    {
      m_dialogPrefab = getResourceManager()->load<Prefab>(m_dialogPrefabPath);
    }

    //------------------------------------------------------------------------------------------------
    void InteractableBuildingDialog::show(
      const CelesteEngine::Handle<CelesteEngine::Screen>& screen,
      const std::unique_ptr<Buildings::Building>& building)
    {
      Handle<GameObject> dialog = m_dialogPrefab->instantiate(screen);

      // Set up close button disabling popup
      dialog->getChildGameObject(0)->findComponent<MouseInteractionHandler>()->getOnLeftButtonClickedEvent().subscribe(
        [&](EventArgs& e, Handle<GameObject> caller) -> void
        {
          caller->getParent()->setActive(false);
          caller->getParent()->setShouldRender(false);

          // This is a hack because without killing the prefab or unsubscribing from the event
          // we need to reset the collider so that this callback is not instantly called when we next left click
          caller->findComponent<Physics::Collider>()->setHitByRay(false);

          // Mark this object to be killed next frame
          Handle<LimitedLifeTime> limitedLifeTime = caller->addComponent<LimitedLifeTime>();
          limitedLifeTime->setLifeTime(0);
        });

      dialog->findChildGameObject(TITLE_TEXT_NAME)->findComponent<TextRenderer>()->addLine(building->getName());
      dialog->findChildGameObject(DESCRIPTION_TEXT_NAME)->findComponent<TextRenderer>()->addLine(building->getDescription());
    }
  }
}