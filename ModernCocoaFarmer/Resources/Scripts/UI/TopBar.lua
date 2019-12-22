local Class = require 'OOP.Class'
local SelectSingleChildCommand = require 'Commands.SelectSingleChildCommand'
local ChildIcon = require 'UI.Family.ChildIcon'
local InGameMenu = require 'UI.InGameMenu'

local TopBar = Class.declare()

---------------------------------------------------------------------------------
TopBar.FAMILY_PANEL_NAME = "FamilyPanelStackPanel"
TopBar.PLAY_BUTTON_NAME = "PlayButton"
TopBar.PAUSE_BUTTON_NAME = "PauseButton"
TopBar.MENU_BUTTON_NAME = "MenuButton"
TopBar.DONATE_BUTTON_NAME = "DonateButton"
TopBar._familyManager = nil
TopBar._childIcons = {}

---------------------------------------------------------------------------------
local function toggleUI(caller, otherButtonName)
    caller:setActive(false)
    caller:setShouldRender(false)

    local otherButton = caller:getParent():findChildGameObject(otherButtonName)
    otherButton:setActive(true)
    otherButton:setShouldRender(true)
end

---------------------------------------------------------------------------------
local function play(eventArgs, caller)
    toggleUI(caller, TopBar.PLAY_BUTTON_NAME)
end

---------------------------------------------------------------------------------
local function pause(eventArgs, caller)
    toggleUI(caller, TopBar.PAUSE_BUTTON_NAME)
end

---------------------------------------------------------------------------------
local function showInGameMenu(eventArgs, caller)
    InGameMenu.show(caller:getScreen())
end

---------------------------------------------------------------------------------
local function showDonateMenu(eventArgs, caller)
end

---------------------------------------------------------------------------------
local function childIconLeftClicked(eventArgs, caller, extraArgs)
    SelectSingleChildCommand.execute(extraArgs.familyManager, extraArgs.childToSelect)
end

---------------------------------------------------------------------------------
function TopBar.new(topBarGameObject, familyManager)
    local topBar = Class.new(TopBar)

    topBar._familyManager = familyManager

    -- Set up family UI being populated
    local familyPanel = topBarGameObject:findChildGameObject(topBar.FAMILY_PANEL_NAME)

    for k, child in ipairs(familyManager.children) do
        local childIcon = ChildIcon.new(familyPanel, child)
        topBar._childIcons[child.name] = childIcon

        local childInteractionHandler = childIcon.gameObject:findComponent("MouseInteractionHandler")
        local extraArgs = {}
        extraArgs.familyManager = familyManager
        extraArgs.childToSelect = childIcon.child
        childInteractionHandler:subscribeOnLeftButtonClickedCallback(childIconLeftClicked, extraArgs)
    end

    topBarGameObject:setupChildLeftClickCallback(topBar.PLAY_BUTTON_NAME, pause)
    topBarGameObject:setupChildLeftClickCallback(topBar.PAUSE_BUTTON_NAME, play)
    topBarGameObject:setupChildLeftClickCallback(topBar.MENU_BUTTON_NAME, showInGameMenu)
    topBarGameObject:setupChildLeftClickCallback(topBar.DONATE_BUTTON_NAME, showDonateMenu)
end

return TopBar