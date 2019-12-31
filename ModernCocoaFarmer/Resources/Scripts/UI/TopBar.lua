local Class = require 'OOP.Class'
local ChildIcon = require 'UI.Family.ChildIcon'
local InGameMenu = require 'UI.InGameMenu'
local MoneyPanel = require 'UI.Information.MoneyPanel'
local TimePanel = require 'UI.Information.TimePanel'

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
local function showInGameMenu(eventArgs, caller)
    InGameMenu.show(caller:getScreen())
end

---------------------------------------------------------------------------------
local function showDonateMenu(eventArgs, caller)
end

---------------------------------------------------------------------------------
local function childIconLeftClicked(eventArgs, caller, extraArgs)
    extraArgs.familyManager:selectOnlyThisChild(extraArgs.childToSelect)
end

---------------------------------------------------------------------------------
function TopBar:new(topBarGameObject, familyManager, moneyManager, timeManager)
    self._familyManager = familyManager
    self._moneyPanel = Class.new(MoneyPanel, topBarGameObject:findChildGameObject(self.MONEY_PANEL_NAME), moneyManager)
    self._timePanel = Class.new(TimePanel, topBarGameObject:findChildGameObject(self.TIME_PANEL_NAME), timeManager)
    self._childIcons = {}

    -- Set up family UI being populated
    local familyPanel = topBarGameObject:findChildGameObject(self.FAMILY_PANEL_NAME)

    local childCount = 0
    while childCount < familyManager:getChildCount() do
        local child = familyManager:getChild(childCount)
        local childIcon = Class.new(ChildIcon, familyPanel, child)
        self._childIcons[child:getName()] = childIcon

        local childInteractionHandler = childIcon.gameObject:findComponent("MouseInteractionHandler")
        local extraArgs = {}
        extraArgs.familyManager = familyManager
        extraArgs.childToSelect = child
        childInteractionHandler:subscribeOnLeftButtonUpCallback(childIconLeftClicked, extraArgs)

        childCount = childCount + 1
    end

    local buttonsStackPanel = topBarGameObject:findChildGameObject(self.UTILITY_BUTTONS_STACK_PANEL_NAME)
    buttonsStackPanel:setupChildLeftButtonUpCallback(self.MENU_BUTTON_NAME, showInGameMenu)
    buttonsStackPanel:setupChildLeftButtonUpCallback(self.DONATE_BUTTON_NAME, showDonateMenu)
end

return TopBar