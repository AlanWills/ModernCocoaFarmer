local Class = require 'OOP.Class'

---------------------------------------------------------------------------------
local Credits = 
{
    CREDITS_SCENE_PATH = path.combine(Resources.getResourcesDirectory(), "Scenes", "Credits.scene"),
    CREDITS_ROOT_NAME = "CreditsScene",
    CLOSE_BUTTON_NAME = "CloseButton",
    OTHER_ASSETS_NAME = "OtherAssets",
    ROLE_NAME = "Role",
    OTHER_ASSETS_CREDITS = 
    {
        "Freepik https://www.flaticon.com/authors/freepik",
        "ttimm54 https://freesound.org/people/ttiimm54/",
    }
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

    local creditsText = ""
    for i, str in ipairs(Credits.OTHER_ASSETS_CREDITS) do
        creditsText = creditsText .. "\n\n" .. str
    end

    local otherAssetsGameObject = rootGameObject:findChild(Credits.OTHER_ASSETS_NAME)
    local roleGameObject = otherAssetsGameObject:findChild(Credits.ROLE_NAME)
    roleGameObject:findComponent("TextRenderer"):setText(creditsText)
end

---------------------------------------------------------------------------------
function Credits.hide()
    GameObject.find(Credits.CREDITS_ROOT_NAME):destroy()
end

return Credits
