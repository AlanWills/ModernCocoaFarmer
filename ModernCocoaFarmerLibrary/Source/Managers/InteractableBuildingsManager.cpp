#include "Managers/InteractableBuildingsManager.h"
#include "Screens/Screen.h"
#include "Input/MouseInteractionHandler.h"
#include "UI/InteractableBuildingDialog.h"
#include "Screens/ScreenUtils.h"
#include "Buildings/Building.h"

using namespace CelesteEngine;
using namespace CelesteEngine::Input;


namespace MCF
{
  namespace Managers
  {
    //------------------------------------------------------------------------------------------------
    const std::string InteractableBuildingsManager::INTERACTABLE_BUILDINGS_NAME = "InteractableBuildings";

    //------------------------------------------------------------------------------------------------
    InteractableBuildingsManager::InteractableBuildingsManager() :
      m_interactableBuildingDialog(new UI::InteractableBuildingDialog()),
      m_buildings()
    {
    }

    //------------------------------------------------------------------------------------------------
    InteractableBuildingsManager::~InteractableBuildingsManager() = default;

    //------------------------------------------------------------------------------------------------
    void InteractableBuildingsManager::initialize(const CelesteEngine::Handle<CelesteEngine::Screen>& screen)
    {
      m_interactableBuildingDialog->initialize();

      Handle<GameObject> interactableBuildings = screen->findGameObject(INTERACTABLE_BUILDINGS_NAME);
      ASSERT(!interactableBuildings.is_null());

      for (size_t childIndex = 0, childCount = interactableBuildings->getChildCount(); childIndex < childCount; ++childIndex)
      {
        Handle<GameObject> interactableBuilding = interactableBuildings->getChildGameObject(childIndex);
        interactableBuilding->findChildGameObject("Icon")->findComponent<MouseInteractionHandler>()->getOnLeftButtonClickedEvent().subscribe(
          [&](EventArgs& e, Handle<GameObject> caller) -> void
          {
            m_interactableBuildingDialog->show(caller->getScreen(), CelesteEngine::ScriptableObject::create<Buildings::Building>("Building"));
          });

        m_buildings.push_back(interactableBuilding);
      }
    }
  }
}