---------------------------------------------------------------------------------
local FinishScene = 
{
    SCENE_PATH = path.combine("Scenes", "Finish.scene"),
    ROOT_NAME = "FinishScene",
    TO_MAIN_MENU_BUTTON_NAME = "ToMainMenuButton",
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
end

---------------------------------------------------------------------------------
function FinishScene.hide(state)
    GameObject.find(FinishScene.ROOT_NAME):destroy()
end

return FinishScene