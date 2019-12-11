local StartGameplayCommand = require 'Commands.StartGameplayCommand'

local MainMenuScreen = {}

---------------------------------------------------------------------------------
MainMenuScreen.MAIN_MENU_SCREEN_PATH = path.combine(Resources.getResourcesDirectory(), "Screens", "MainMenu.screen")
MainMenuScreen.PLAY_BUTTON_NAME = "PlayButton"
MainMenuScreen.OPTIONS_BUTTON_NAME = "OptionsButton"
MainMenuScreen.EXIT_BUTTON_NAME = "ExitButton"

---------------------------------------------------------------------------------
local function play(eventArgs, caller)
    caller:getScreen():die()
    StartGameplayCommand.execute()
end

---------------------------------------------------------------------------------
local function toOptions(eventArgs, caller)
    caller:getScreen():die()

    local OptionsScreen = require 'Screens.OptionsScreen'
    OptionsScreen.show()
end

---------------------------------------------------------------------------------
local function exitGame(eventArgs, caller)
    exit()
end

---------------------------------------------------------------------------------
function MainMenuScreen.show()
    local mainMenuScreen = Screen.load(MainMenuScreen.MAIN_MENU_SCREEN_PATH)
    local layoutStackPanel = mainMenuScreen:findGameObject("Canvas2"):findChildGameObject("LayoutStackPanel")
    
    layoutStackPanel:setupChildLeftClickCallback(MainMenuScreen.PLAY_BUTTON_NAME, play)
    layoutStackPanel:setupChildLeftClickCallback(MainMenuScreen.OPTIONS_BUTTON_NAME, toOptions)
    layoutStackPanel:setupChildLeftClickCallback(MainMenuScreen.EXIT_BUTTON_NAME, exitGame)
end

return MainMenuScreen