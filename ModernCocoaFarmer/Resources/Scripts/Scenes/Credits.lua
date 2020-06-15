local Class = require 'OOP.Class'

---------------------------------------------------------------------------------
local Credits = 
{
    CREDITS_SCENE_PATH = path.combine(Resources.getResourcesDirectory(), "Scenes", "Credits.scene"),
    CREDITS_ROOT_NAME = "CreditsScene",
    CLOSE_BUTTON_NAME = "CloseButton",
}

---------------------------------------------------------------------------------
local function toMainMenu(caller)
    local Credits = require 'Scenes.Credits'
    Credits.hide()

    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.show()
end

---------------------------------------------------------------------------------
function Credits.show()
    Scene.load(Credits.CREDITS_SCENE_PATH)
    local rootGameObject = GameObject.find(Credits.CREDITS_ROOT_NAME)
    
    rootGameObject:setupChildLeftButtonUpCallback(Credits.CLOSE_BUTTON_NAME, toMainMenu)
end

---------------------------------------------------------------------------------
function Credits.hide()
    GameObject.find(Credits.CREDITS_ROOT_NAME):destroy()
end

return Credits
