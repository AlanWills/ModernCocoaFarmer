local ibd = {}

ibd.DIALOG_PREFAB_PATH = "Prefabs\\UI\\InteractableBuildingDialog.prefab"
ibd.TITLE_TEXT_NAME = "TitleText"
ibd.DESCRIPTION_TEXT_NAME = "DescriptionText"
ibd.CLOSE_BUTTON_NAME = "CloseButton"

function ibd.load()
    return Resources.loadPrefab(ibd.DIALOG_PREFAB_PATH)
end

function close(eventArgs, caller)
    --caller:getParent():setShouldRender(false)

    --local limitedLifeTime = caller:addComponent("LimitedLifeTime")
    --limitedLifeTime:setLifeTime(0)
    assert(false)
end

function ibd.show(screen)
    local dialogPrefab = ibd.load()
    local dialogGameObject = dialogPrefab:instantiate(screen)
    local closeButton = dialogGameObject:findChildGameObject(ibd.CLOSE_BUTTON_NAME)
    local mouseInteractionHandler = closeButton:findComponent("MouseInteractionHandler")
    mouseInteractionHandler:subscribeOnLeftButtonClickedCallback("close")
end

return ibd