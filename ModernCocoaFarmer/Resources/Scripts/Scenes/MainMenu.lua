local StartGameplayCommand = require 'Commands.StartGameplayCommand'

---------------------------------------------------------------------------------
local MainMenu = 
{
    MAIN_MENU_SCENE_PATH = path.combine(Resources.getResourcesDirectory(), "Scenes", "MainMenu.scene"),
    MAIN_MENU_ROOT_NAME = "MainMenuScene",
    PLAY_BUTTON_NAME = "PlayButton",
    OPTIONS_BUTTON_NAME = "OptionsButton",
    EXIT_BUTTON_NAME = "ExitButton",
}

---------------------------------------------------------------------------------
local function play(caller)
    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.hide()

    --StartGameplayCommand.execute()
end

---------------------------------------------------------------------------------
local function toOptions(caller)
    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.hide()

    local Options = require 'Scenes.Options'
    Options.show()
end

---------------------------------------------------------------------------------
local function exitGame(caller)
    exit()
end

---------------------------------------------------------------------------------
function MainMenu.show()
    Scene.load(MainMenu.MAIN_MENU_SCENE_PATH)
    local layoutStackPanel = GameObject.find("Canvas2"):findChild("LayoutStackPanel")
    
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenu.PLAY_BUTTON_NAME, play)
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenu.OPTIONS_BUTTON_NAME, toOptions)
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenu.EXIT_BUTTON_NAME, exitGame)
end

---------------------------------------------------------------------------------
function MainMenu.hide()
    GameObject.find(MainMenu.MAIN_MENU_ROOT_NAME):destroy()
end

return MainMenu
