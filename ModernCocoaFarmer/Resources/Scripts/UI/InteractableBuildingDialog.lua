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
function ibd.show(screen, buildingInformation)
    local dialogPrefab = ibd.load()
    local dialogGameObject = dialogPrefab:instantiate(screen)

    local titleText = dialogGameObject:findChildGameObject(ibd.TITLE_TEXT_NAME)
    titleText:findComponent("TextRenderer"):setLine

    local closeButton = dialogGameObject:findChildGameObject(ibd.CLOSE_BUTTON_NAME)
    local mouseInteractionHandler = closeButton:findComponent("MouseInteractionHandler")
    mouseInteractionHandler:subscribeOnLeftButtonClickedCallback(closeCallback)
end

return ibd