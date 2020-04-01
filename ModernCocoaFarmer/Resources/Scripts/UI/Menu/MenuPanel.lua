local Class = require 'OOP.Class'
local InGameMenu = require 'UI.InGameMenu'

---------------------------------------------------------------------------------
local MenuPanel =
{
    MENU_BUTTON_NAME = "MenuButton",
}

---------------------------------------------------------------------------------
local function showInGameMenu(caller)
    InGameMenu.show()
end

---------------------------------------------------------------------------------
function MenuPanel:new(commandManager, dataStore, menuPanelGameObject)
    menuPanelGameObject:setupChildLeftButtonUpCallback(self.MENU_BUTTON_NAME, showInGameMenu)
end

---------------------------------------------------------------------------------
function MenuPanel:updateUI()
end

return MenuPanel