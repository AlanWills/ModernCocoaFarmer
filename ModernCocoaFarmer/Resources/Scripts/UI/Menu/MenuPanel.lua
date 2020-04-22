local Class = require 'OOP.Class'
local ShowInGameMenuDialog = require 'Commands.UI.Menu.ShowInGameMenuDialog'

---------------------------------------------------------------------------------
local MenuPanel =
{
    MENU_BUTTON_NAME = "MenuButton",
}

---------------------------------------------------------------------------------
local function showInGameMenu(caller, self)
    self._commandManager:execute(ShowInGameMenuDialog)
end

---------------------------------------------------------------------------------
function MenuPanel:new(commandManager, dataStore, menuPanelGameObject)
    self._commandManager = commandManager

    menuPanelGameObject:setupChildLeftButtonUpCallback(self.MENU_BUTTON_NAME, showInGameMenu, self)
end

---------------------------------------------------------------------------------
function MenuPanel:updateUI()
end

return MenuPanel