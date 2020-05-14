---------------------------------------------------------------------------------
local FinishScene = 
{
    SCENE_PATH = path.combine("Scenes", "Finish.scene"),
    CHILD_FINISH_NAME_PREFAB_PATH = path.combine("Prefabs", "Finish", "Family", "ChildFinishName.prefab"),
    CHILD_FINISH_STATUS_PREFAB_PATH = path.combine("Prefabs", "Finish", "Family", "ChildFinishStatus.prefab"),
    ROOT_NAME = "FinishScene",
    CHILD_FINISH_NAME_STACK_PANEL_NAME = "ChildrenFinishNameStackPanel",
    CHILD_FINISH_STATUS_STACK_PANEL_NAME = "ChildrenFinishStatusStackPanel",
    TO_MAIN_MENU_BUTTON_NAME = "ToMainMenuButton",
    CHILD_FINISH_NAME_NAME = "ChildFinishName",
    CHILD_FINISH_STATUS_NAME = "ChildFinishStatus",
}

---------------------------------------------------------------------------------
local function toMainMenuButtonCallback(caller)
    local MainMenuScene = require 'Scenes.MainMenu'

    FinishScene.hide()
    MainMenuScene.show()
end

---------------------------------------------------------------------------------
function FinishScene.show(graduatedChildren, deadChildren)
    Scene.load(FinishScene.SCENE_PATH)

    local rootGameObject = GameObject.find(FinishScene.ROOT_NAME)
    rootGameObject:setupChildLeftButtonUpCallback(FinishScene.TO_MAIN_MENU_BUTTON_NAME, toMainMenuButtonCallback)
    
    local childrenName = GameObject.find(FinishScene.CHILD_FINISH_NAME_STACK_PANEL_NAME)
    local childrenStatus = GameObject.find(FinishScene.CHILD_FINISH_STATUS_STACK_PANEL_NAME)

    local childrenNameStackPanel = childrenName:findComponent("StackPanel")
    local childrenStatusStackPanel = childrenStatus:findComponent("StackPanel")
    
    local childNamePrefab = Resources.loadPrefab(FinishScene.CHILD_FINISH_NAME_PREFAB_PATH)
    local childStatusPrefab = Resources.loadPrefab(FinishScene.CHILD_FINISH_STATUS_PREFAB_PATH)

    for k, childName in ipairs(graduatedChildren) do
        childrenNameStackPanel:addChild(FinishScene.createChildName(childNamePrefab, childName))
        childrenStatusStackPanel:addChild(FinishScene.createChildStatus(childStatusPrefab, childName, "Graduated"))
    end
    
    for k, childName in ipairs(deadChildren) do
        childrenNameStackPanel:addChild(FinishScene.createChildName(childNamePrefab, childName))
        childrenStatusStackPanel:addChild(FinishScene.createChildStatus(childStatusPrefab, childName, "Died"))
    end
end

---------------------------------------------------------------------------------
function FinishScene.createChildName(childNamePrefab, childName)
    local childNameGameObject = childNamePrefab:instantiate()
    childNameGameObject:setName(childName .. "Name")
    childNameGameObject:findComponent("TextRenderer"):setText(childName .. ": ")

    return childNameGameObject
end

---------------------------------------------------------------------------------
function FinishScene.createChildStatus(childStatusPrefab, childName, status)
    local childStatusGameObject = childStatusPrefab:instantiate()
    childStatusGameObject:setName(childName .. "Status")
    childStatusGameObject:findComponent("TextRenderer"):setText(status)

    return childStatusGameObject
end

---------------------------------------------------------------------------------
function FinishScene.hide(state)
    GameObject.find(FinishScene.ROOT_NAME):destroy()
end

return FinishScene