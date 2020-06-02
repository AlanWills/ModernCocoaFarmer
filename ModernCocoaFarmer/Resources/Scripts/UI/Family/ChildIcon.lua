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
    CONSTANTS_NAME = "Constants",
    CHILD_ROOT_KEY_NAME = "ChildRootKey",
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
    self._commandManager:execute(ToggleChildSelection, self._childName)
end

---------------------------------------------------------------------------------
function ChildIcon:new(commandManager, dataStore, gameObject, childName)
    self._commandManager = commandManager
    self._dataStore = dataStore
    self._childName = childName
    self._gameObject = gameObject
    self._animator = gameObject:findChild(self.CHILD_ACTIVE_IMAGE):findComponent("Animator")
    self._selectedIcon = gameObject:findChild(self.CHILD_ACTIVE_IMAGE):findChild(self.CHILD_SELECTED_ICON_NAME)
    self._statsDialog = Class.new(ChildStatsPanel, dataStore, childName, gameObject)
    self._statsDialog:hide()

    gameObject:setName(childName)

    local childInteractionHandler = gameObject:findChild(self.CHILD_ACTIVE_IMAGE):findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnEnterCallback(showChildStats, self)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildStats, self)
    childInteractionHandler:subscribeOnLeftButtonUpCallback(childIconLeftClickedCallback, self)

    local childRootKeyGameObject = gameObject:findChild(self.CONSTANTS_NAME):findChild(self.CHILD_ROOT_KEY_NAME)
    childRootKeyGameObject:findComponent("Constant"):setValue(FamilyDataSources.CHILDREN .. "." .. childName)
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
    local childObject = self._dataStore:getObject(FamilyDataSources.CHILDREN .. "." .. self._childName)
    local childSelected = childObject:getBool(FamilyDataSources.IS_SELECTED)

    if childSelected then
        self._animator:play()
    else
        self._animator:stop()
    end

    self._selectedIcon:setActive(childSelected)
end

return ChildIcon