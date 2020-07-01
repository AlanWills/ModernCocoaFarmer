local Class = require 'OOP.Class'
local ShowInGameMenuDialog = require 'Commands.UI.Menu.ShowInGameMenuDialog'
local SaveGame = require 'Commands.State.SaveGame'
local GameplayState = require 'State.GameplayState'

---------------------------------------------------------------------------------
local MenuPanel =
{
    MENU_BUTTON_NAME = "MenuButton",
    SAVE_BUTTON_NAME = "SaveButton",
}

---------------------------------------------------------------------------------
function MenuPanel.save(caller, self)
    self._commandManager:execute(SaveGame)
end

---------------------------------------------------------------------------------
function MenuPanel.showInGameMenu(caller, self)
    self._commandManager:execute(ShowInGameMenuDialog)
end

---------------------------------------------------------------------------------
function MenuPanel:new(commandManager, menuPanelGameObject)
    self._commandManager = commandManager

    menuPanelGameObject:setupChildLeftButtonUpCallback(self.SAVE_BUTTON_NAME, MenuPanel.save, self)
    menuPanelGameObject:setupChildLeftButtonUpCallback(self.MENU_BUTTON_NAME, MenuPanel.showInGameMenu, self)
end

return MenuPanel