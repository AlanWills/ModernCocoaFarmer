local Class = require 'OOP.Class'
local ToggleChildSelection = require 'Commands.Family.ToggleChildSelection'
local ChildStatsPanel = require 'UI.Family.ChildStatsPanel'

---------------------------------------------------------------------------------
local ChildIcon =
{
    CHILD_ACTIVE_IMAGE = "ChildActiveImage",
    CHILD_GRADUATED_IMAGE = "ChildGraduatedImage",
    CHILD_DEAD_IMAGE = "ChildDeadImage",
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
local function childIconLeftClickedCallback(caller, self)
    self._commandManager:execute(ToggleChildSelection, self._child:getName())
end

---------------------------------------------------------------------------------
function ChildIcon:new(commandManager, dataStore, gameObject, child)
    self._commandManager = commandManager
    self._dataStore = dataStore
    self._child = child
    self._gameObject = gameObject
    self._animator = gameObject:findChild(self.CHILD_ACTIVE_IMAGE):findComponent("Animator")
    self._selectedIcon = gameObject:findChild(self.CHILD_ACTIVE_IMAGE):findChild(self.CHILD_SELECTED_ICON_NAME)
    self._statsDialog = Class.new(ChildStatsPanel, dataStore, child:getName(), gameObject)
    self._statsDialog:hide()

    gameObject:setName(child:getName())

    local childInteractionHandler = gameObject:findChild(self.CHILD_ACTIVE_IMAGE):findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnEnterCallback(showChildStats, self)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildStats, self)
    childInteractionHandler:subscribeOnLeftButtonUpCallback(childIconLeftClickedCallback, self)

    self:setNameText(child:getName())
end

---------------------------------------------------------------------------------
function ChildIcon:setNameText(childName)
    -- Hook these up to the data system when we implement the components
    self._gameObject:findChild(self.CHILD_ACTIVE_IMAGE):findChild(self.CHILD_NAME_NAME):findComponent("TextRenderer"):setText(childName)
    self._gameObject:findChild(self.CHILD_GRADUATED_IMAGE):findChild(self.CHILD_NAME_NAME):findComponent("TextRenderer"):setText(childName)
    self._gameObject:findChild(self.CHILD_DEAD_IMAGE):findChild(self.CHILD_NAME_NAME):findComponent("TextRenderer"):setText(childName)
end

---------------------------------------------------------------------------------
function ChildIcon:updateUI()
    if self._statsDialog:isShowing() then
        self._statsDialog:updateUI()
    end

    self:updateIconUI()
    self:updateSelectionUI()
end

---------------------------------------------------------------------------------
function ChildIcon:updateIconUI()
    -- Hook these up to the data system when we implement the components
    -- Then can remove the update call every frame

    self._gameObject:findChild(self.CHILD_ACTIVE_IMAGE):setActive(self._child:isActivated())
    self._gameObject:findChild(self.CHILD_GRADUATED_IMAGE):setActive(self._child:isGraduated())
    self._gameObject:findChild(self.CHILD_DEAD_IMAGE):setActive(self._child:isDead())
end

---------------------------------------------------------------------------------
function ChildIcon:updateSelectionUI()
    local childObject = self._dataStore:getObject(FamilyDataSources.CHILDREN .. "." .. self._child:getName())
    local childSelected = childObject:getBool(FamilyDataSources.IS_SELECTED)

    if childSelected then
        self._animator:play()
    else
        self._animator:stop()
    end

    self._selectedIcon:setActive(childSelected)
end

return ChildIcon