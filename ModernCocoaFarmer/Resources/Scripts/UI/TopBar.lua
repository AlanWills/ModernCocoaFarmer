local ChildIcon = require 'UI.Family.ChildIcon'
local InGameMenu = require 'UI.InGameMenu'

local TopBar = {}

---------------------------------------------------------------------------------
TopBar.FAMILY_PANEL_NAME = "FamilyPanelStackPanel"
TopBar.PLAY_BUTTON_NAME = "PlayButton"
TopBar.PAUSE_BUTTON_NAME = "PauseButton"
TopBar.MENU_BUTTON_NAME = "MenuButton"
TopBar.DONATE_BUTTON_NAME = "DonateButton"

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
function TopBar.initialize(topBarGameObject, familyManager)
    -- Set up family UI being populated
    local familyPanel = topBarGameObject:findChildGameObject(TopBar.FAMILY_PANEL_NAME)

    for k, v in ipairs(familyManager.children) do
        local childInstance = ChildIcon.initialize(familyPanel, v)
    end

    topBarGameObject:setupChildLeftClickCallback(TopBar.PLAY_BUTTON_NAME, pause)
    topBarGameObject:setupChildLeftClickCallback(TopBar.PAUSE_BUTTON_NAME, play)
    topBarGameObject:setupChildLeftClickCallback(TopBar.MENU_BUTTON_NAME, showInGameMenu)
    topBarGameObject:setupChildLeftClickCallback(TopBar.DONATE_BUTTON_NAME, showDonateMenu)
end

return TopBar