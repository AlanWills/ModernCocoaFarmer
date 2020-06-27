local Class = require 'OOP.Class'
local GameplayState = require 'State.GameplayState'

---------------------------------------------------------------------------------
local MainMenu = 
{
    MAIN_MENU_SCENE_PATH = path.combine(Resources.getResourcesDirectory(), "Scenes", "MainMenu.scene"),
    MAIN_MENU_ROOT_NAME = "MainMenuScene",
    PLAY_BUTTON_NAME = "PlayButton",
    CONTINUE_BUTTON_NAME = "ContinueButton",
    OPTIONS_BUTTON_NAME = "OptionsButton",
    CREDITS_BUTTON_NAME = "CreditsButton",
    EXIT_BUTTON_NAME = "ExitButton",
}

---------------------------------------------------------------------------------
local function play(caller)
    local MainMenu = require 'Scenes.MainMenu'
    local NewGame = require 'Commands.State.NewGame'

    MainMenu.hide()
    Class.new(NewGame):execute()
end

---------------------------------------------------------------------------------
local function continue(caller)
    local MainMenu = require 'Scenes.MainMenu'
    local LoadGame = require 'Commands.State.LoadGame'

    MainMenu.hide()
    Class.new(LoadGame):execute()
end

---------------------------------------------------------------------------------
local function toOptions(caller)
    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.hide()

    local Options = require 'Scenes.Options'
    Options.show()
end

---------------------------------------------------------------------------------
local function toCredits(caller)
    local MainMenu = require 'Scenes.MainMenu'
    MainMenu.hide()

    local Credits = require 'Scenes.Credits'
    Credits.show()
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
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenu.CONTINUE_BUTTON_NAME, continue)
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenu.OPTIONS_BUTTON_NAME, toOptions)
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenu.CREDITS_BUTTON_NAME, toCredits)
    layoutStackPanel:setupChildLeftButtonUpCallback(MainMenu.EXIT_BUTTON_NAME, exitGame)

    local continueButton = layoutStackPanel:findChild(MainMenu.CONTINUE_BUTTON_NAME)
    continueButton:setActive(GameplayState.hasSave())
    layoutStackPanel:findComponent("StackPanel"):layout()
end

---------------------------------------------------------------------------------
function MainMenu.hide()
    GameObject.find(MainMenu.MAIN_MENU_ROOT_NAME):destroy()
end

return MainMenu
