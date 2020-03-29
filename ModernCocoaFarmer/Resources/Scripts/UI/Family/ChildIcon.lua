local Class = require 'OOP.Class'
local ChildStatsPanel = require 'UI.Family.ChildStatsPanel'

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
    self._statsDialog = Class.new(ChildStatsPanel, dataStore, child:getName(), gameObject)
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
    local childObject = self._dataStore:getObject(FamilyDataSources.CHILDREN .. "." .. self._child:getName())
    local childSelected = childObject:getBool(FamilyDataSources.IS_SELECTED)
    local animator = self._gameObject:findComponent("Animator")

    if childSelected then
        animator:play()
    else
        animator:stop()
    end

    self._selectedIcon:setActive(childSelected)
end

return ChildIcon