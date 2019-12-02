local ChildIcon = require 'UI.Family.ChildIcon'
local InGameMenu = require 'UI.InGameMenu'

local TopBar = {}

---------------------------------------------------------------------------------
TopBar.FAMILY_PANEL_NAME = "FamilyPanelStackPanel"
TopBar.MENU_BUTTON_NAME = "MenuButton"

---------------------------------------------------------------------------------
local function showInGameMenu(eventArgs, caller)
    InGameMenu.show(caller:getScreen())
end

---------------------------------------------------------------------------------
function TopBar.initialize(topBarGameObject, familyManager)
    -- Set up family UI being populated
    local familyPanel = topBarGameObject:findChildGameObject(TopBar.FAMILY_PANEL_NAME)

    for k, v in ipairs(familyManager.children) do
        local childInstance = ChildIcon.initialize(familyPanel, v)
    end

    local menuButton = topBarGameObject:findChildGameObject(TopBar.MENU_BUTTON_NAME)
    local menuButtonInteractionHandler = menuButton:findComponent("MouseInteractionHandler")
    menuButtonInteractionHandler:subscribeOnLeftButtonClickedCallback(showInGameMenu)
end

return TopBar