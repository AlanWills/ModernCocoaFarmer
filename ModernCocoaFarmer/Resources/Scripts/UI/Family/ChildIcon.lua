local Class = require 'OOP.Class'
local ChildStatsDialog = require 'UI.Family.ChildStatsDialog'

---------------------------------------------------------------------------------
local ChildIcon =
{
    CHILD_SELECTED_ICON_NAME = "ChildSelectedIcon",
    CHILD_NAME_NAME = "ChildName",
}

---------------------------------------------------------------------------------
local function showChildStats(caller, self)
    self._statsDialog:updateUI()
    self._statsDialog:show()
end

---------------------------------------------------------------------------------
local function hideChildStats(caller, self)
    self._statsDialog:hide()
end

---------------------------------------------------------------------------------
function ChildIcon:new(dataStore, gameObject, child)
    self._dataStore = dataStore
    self._child = child
    self._gameObject = gameObject
    self._selectedIcon = gameObject:findChild(self.CHILD_SELECTED_ICON_NAME)
    self._statsDialog = Class.new(ChildStatsDialog, gameObject, child)
    self._statsDialog:hide()

    gameObject:setName(child:getName())
    gameObject:setActive(true)

    local childInteractionHandler = gameObject:findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnEnterCallback(showChildStats, self)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildStats, self)

    local childName = gameObject:findChild(self.CHILD_NAME_NAME)
    childName:findComponent("TextRenderer"):setText(child:getName())
end

---------------------------------------------------------------------------------
function ChildIcon:updateUI()
    if self._statsDialog:isShowing() then
        self._statsDialog:updateUI()
    end

    self:updateSelectionUI()
end

---------------------------------------------------------------------------------
function ChildIcon:updateSelectionUI()
    local childSelected = self._dataStore:getBoolElement(FamilyDataSources.CHILD_SELECTION_STATUS, self._child:getName())
    local animator = self._gameObject:findComponent("Animator")

    if childSelected then
        animator:play()
    else
        animator:stop()
    end

    self._selectedIcon:setActive(childSelected)
end

return ChildIcon