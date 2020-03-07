local StartGameplayCommand = require 'Commands.StartGameplayCommand'

local MainMenuScene = {}

---------------------------------------------------------------------------------
MainMenuScene.MAIN_MENU_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Scenes", "MainMenu.scene")
MainMenuScene.PLAY_BUTTON_NAME = "PlayButton"
MainMenuScene.OPTIONS_BUTTON_NAME = "OptionsButton"
MainMenuScene.EXIT_BUTTON_NAME = "ExitButton"

---------------------------------------------------------------------------------
local function play(caller)
    caller:getScene():die()
    StartGameplayCommand.execute()
end

---------------------------------------------------------------------------------
local function toOptions(caller)
    caller:getScene():die()

    local OptionsScene = require 'Scenes.Options'
    OptionsScene.show()
end

---------------------------------------------------------------------------------
local function exitGame(caller)
    exit()
end

---------------------------------------------------------------------------------
function MainMenuScene.show()
    Scene.load(MainMenuScene.MAIN_MENU_SCREEN_PATH)
    local layoutStackPanel = GameObject.find("Canvas2"):findChild("LayoutStackPanel")
    
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenuScene.PLAY_BUTTON_NAME, play)
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenuScene.OPTIONS_BUTTON_NAME, toOptions)
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenuScene.EXIT_BUTTON_NAME, exitGame)
end

return MainMenuScene
