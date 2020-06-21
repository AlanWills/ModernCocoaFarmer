local Class = require 'OOP.Class'
local ShowInGameMenuDialog = require 'Commands.UI.Menu.ShowInGameMenuDialog'
local Save = require 'Commands.State.Save'
local GameplayState = require 'State.GameplayState'

---------------------------------------------------------------------------------
local MenuPanel =
{
    MENU_BUTTON_NAME = "MenuButton",
    SAVE_BUTTON_NAME = "SaveButton",
}

---------------------------------------------------------------------------------
local function save(caller, self)
    self._commandManager:execute(Save, GameplayState.SAVE_DIRECTORY)
end

---------------------------------------------------------------------------------
local function showInGameMenu(caller, self)
    self._commandManager:execute(ShowInGameMenuDialog)
end

---------------------------------------------------------------------------------
function MenuPanel:new(commandManager, menuPanelGameObject)
    self._commandManager = commandManager

    menuPanelGameObject:setupChildLeftButtonUpCallback(self.SAVE_BUTTON_NAME, save, self)
    menuPanelGameObject:setupChildLeftButtonUpCallback(self.MENU_BUTTON_NAME, showInGameMenu, self)
end

return MenuPanel