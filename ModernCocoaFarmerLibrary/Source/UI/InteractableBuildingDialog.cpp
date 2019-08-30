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
    const std::string InteractableBuildingDialog::CLOSE_BUTTON_NAME = "CloseButton";

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
      dialog->findChildGameObject(CLOSE_BUTTON_NAME)->findComponent<MouseInteractionHandler>()->getOnLeftButtonClickedEvent().subscribe(
        [&](EventArgs& e, Handle<GameObject> caller) -> void
        {
          caller->getParent()->setShouldRender(false);

          // Mark this object to be killed next frame
          Handle<LimitedLifeTime> limitedLifeTime = caller->addComponent<LimitedLifeTime>();
          limitedLifeTime->setLifeTime(0);
        });

      //dialog->findChildGameObject(TITLE_TEXT_NAME)->findComponent<TextRenderer>()->addLine(building->getName());
      //dialog->findChildGameObject(DESCRIPTION_TEXT_NAME)->findComponent<TextRenderer>()->addLine(building->getDescription());
    }
  }
}