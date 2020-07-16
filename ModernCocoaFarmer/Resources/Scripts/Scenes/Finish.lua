---------------------------------------------------------------------------------
local FinishScene = 
{
    SCENE_PATH = path.combine("Scenes", "Finish.scene"),
    CHILD_FINISH_NAME_PREFAB_PATH = path.combine("Prefabs", "Finish", "Family", "ChildFinishName.prefab"),
    ROOT_NAME = "FinishScene",
    CHILDREN_GRADUATED_STACK_PANEL_NAME = "ChildrenGraduatedStackPanel",
    CHILDREN_DIED_STACK_PANEL_NAME = "ChildrenDiedStackPanel",
    TO_MAIN_MENU_BUTTON_NAME = "ToMainMenuButton",
}

---------------------------------------------------------------------------------
local function toMainMenuButtonCallback(caller)
    local MainMenuScene = require 'Scenes.MainMenu'
    local MenuMusic = require 'Scenes.MenuMusic'

    FinishScene.hide()
    MenuMusic.show()
    MainMenuScene.show()
end

---------------------------------------------------------------------------------
function FinishScene.show(graduatedChildren, deadChildren)
    Scene.load(FinishScene.SCENE_PATH)

    local rootGameObject = GameObject.find(FinishScene.ROOT_NAME)
    rootGameObject:setupChildLeftButtonUpCallback(FinishScene.TO_MAIN_MENU_BUTTON_NAME, toMainMenuButtonCallback)
    
    local childrenGraduated = GameObject.find(FinishScene.CHILDREN_GRADUATED_STACK_PANEL_NAME)
    local childrenDied = GameObject.find(FinishScene.CHILDREN_DIED_STACK_PANEL_NAME)

    local childrenGraduatedStackPanel = childrenGraduated:findComponent("StackPanel")
    local childrenDiedStackPanel = childrenDied:findComponent("StackPanel")
    
    local childNamePrefab = Resources.loadPrefab(FinishScene.CHILD_FINISH_NAME_PREFAB_PATH)

    for k, childName in ipairs(graduatedChildren) do
        childrenGraduatedStackPanel:addChild(FinishScene.createChildName(childNamePrefab, childName))
    end
    
    for k, childName in ipairs(deadChildren) do
        childrenDiedStackPanel:addChild(FinishScene.createChildName(childNamePrefab, childName))
    end
end

---------------------------------------------------------------------------------
function FinishScene.createChildName(childNamePrefab, childName)
    local childNameGameObject = childNamePrefab:instantiate()
    childNameGameObject:setName(childName .. "Name")
    childNameGameObject:findComponent("TextRenderer"):setText(childName)

    return childNameGameObject
end

---------------------------------------------------------------------------------
function FinishScene.hide(state)
    GameObject.find(FinishScene.ROOT_NAME):destroy()
end

return FinishScene