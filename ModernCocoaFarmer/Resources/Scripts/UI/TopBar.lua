local Class = require 'OOP.Class'
local MoneyPanel = require 'UI.Money.MoneyPanel'
local FamilyPanel = require 'UI.Family.FamilyPanel'
local TimePanel = require 'UI.Time.TimePanel'
local MenuPanel = require 'UI.Menu.MenuPanel'

---------------------------------------------------------------------------------
local TopBar =
{
    MONEY_PANEL_NAME = "MoneyPanel",
    FAMILY_PANEL_NAME = "FamilyPanel",
    TIME_PANEL_NAME = "TimePanel",
    MENU_PANEL_NAME = "MenuPanel",
}

---------------------------------------------------------------------------------
function TopBar:new(commandManager, dataStore, topBarGameObject)
    self._moneyPanel = Class.new(MoneyPanel, dataStore, topBarGameObject:findChild(self.MONEY_PANEL_NAME))
    self._familyPanel = Class.new(FamilyPanel, commandManager, dataStore, topBarGameObject:findChild(self.FAMILY_PANEL_NAME))
    self._timePanel = Class.new(TimePanel, commandManager, dataStore, topBarGameObject:findChild(self.TIME_PANEL_NAME))
    self._menuPanel = Class.new(MenuPanel, commandManager, dataStore, topBarGameObject:findChild(self.MENU_PANEL_NAME))
end

---------------------------------------------------------------------------------
function TopBar:updateUI()
    self._moneyPanel:updateUI()
    self._familyPanel:updateUI()
    self._timePanel:updateUI()
    self._menuPanel:updateUI()
end

return TopBar