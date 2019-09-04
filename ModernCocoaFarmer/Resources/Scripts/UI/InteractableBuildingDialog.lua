local ibd = {}

----------------------------------------------------------------------------------------
ibd.DIALOG_PREFAB_PATH = "Prefabs\\UI\\InteractableBuildingDialog.prefab"
ibd.TITLE_TEXT_NAME = "TitleText"
ibd.DESCRIPTION_TEXT_NAME = "DescriptionText"
ibd.CLOSE_BUTTON_NAME = "CloseButton"

----------------------------------------------------------------------------------------
local function closeCallback(eventArgs, caller)
    caller:getParent():setShouldRender(false)

    local limitedLifeTime = caller:addComponent("LimitedLifeTime")
    limitedLifeTime:setLifeTime(0)
end

----------------------------------------------------------------------------------------
function ibd.load()
    return Resources.loadPrefab(ibd.DIALOG_PREFAB_PATH)
end

----------------------------------------------------------------------------------------
function ibd.show(screen)
    local dialogPrefab = ibd.load()
    local dialogGameObject = dialogPrefab:instantiate(screen)
    local closeButton = dialogGameObject:findChildGameObject(ibd.CLOSE_BUTTON_NAME)
    local mouseInteractionHandler = closeButton:findComponent("MouseInteractionHandler")
    mouseInteractionHandler:subscribeOnLeftButtonClickedCallback(closeCallback)
end

return ibd

--[[
InteractableBuildings

    Handle<GameObject> interactableBuildings = screen->findGameObject(INTERACTABLE_BUILDINGS_NAME);
      ASSERT(!interactableBuildings.is_null());

      for (size_t childIndex = 0, childCount = interactableBuildings->getChildCount(); childIndex < childCount; ++childIndex)
      {
        Handle<GameObject> interactableBuilding = interactableBuildings->getChildGameObject(childIndex);
        interactableBuilding->findChildGameObject("Icon")->findComponent<MouseInteractionHandler>()->getOnLeftButtonClickedEvent().subscribe(
          [&](EventArgs& e, Handle<GameObject> caller) -> void
          {
            //m_interactableBuildingDialog->show(caller->getScreen(), CelesteEngine::ScriptableObject::create<Buildings::BuildingInformation>("Building"));
          });

        m_buildings.push_back(interactableBuilding);
      }
]]