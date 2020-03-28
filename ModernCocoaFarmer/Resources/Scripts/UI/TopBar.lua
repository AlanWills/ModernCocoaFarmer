local Class = require 'OOP.Class'
local InGameMenu = require 'UI.InGameMenu'
local MoneyPanel = require 'UI.Money.MoneyPanel'
local FamilyPanel = require 'UI.Family.FamilyPanel'
local TimePanel = require 'UI.Time.TimePanel'

---------------------------------------------------------------------------------
local TopBar =
{
    MONEY_PANEL_NAME = "MoneyPanel",
    FAMILY_PANEL_NAME = "FamilyPanel",
    TIME_PANEL_NAME = "TimePanel",
    UTILITY_BUTTONS_STACK_PANEL_NAME = "UtilityButtonsStackPanel",
    MENU_BUTTON_NAME = "MenuButton",
    DONATE_BUTTON_NAME = "DonateButton"
}

---------------------------------------------------------------------------------
local function showInGameMenu(caller)
    InGameMenu.show()
end

---------------------------------------------------------------------------------
local function showDonateMenu(caller)
end

---------------------------------------------------------------------------------
function TopBar:new(commandManager, dataStore, topBarGameObject)
    self._moneyPanel = Class.new(MoneyPanel, dataStore, topBarGameObject:findChild(self.MONEY_PANEL_NAME))
    self._familyPanel = Class.new(FamilyPanel, commandManager, dataStore, topBarGameObject:findChild(self.FAMILY_PANEL_NAME))
    self._timePanel = Class.new(TimePanel, commandManager, dataStore, topBarGameObject:findChild(self.TIME_PANEL_NAME))
    
    local buttonsStackPanel = topBarGameObject:findChild(self.UTILITY_BUTTONS_STACK_PANEL_NAME)
    buttonsStackPanel:setupChildLeftButtonUpCallback(self.MENU_BUTTON_NAME, showInGameMenu)
    buttonsStackPanel:setupChildLeftButtonUpCallback(self.DONATE_BUTTON_NAME, showDonateMenu)
end

---------------------------------------------------------------------------------
function TopBar:updateUI()
    self._moneyPanel:updateUI()
    self._familyPanel:updateUI()
    self._timePanel:updateUI()
end

return TopBar