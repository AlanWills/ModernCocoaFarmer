local Class = require 'OOP.Class'
local ChildStatsDialog = require 'UI.Family.ChildStatsDialog'

---------------------------------------------------------------------------------
local ChildIcon =
{
    CHILD_ICON_PREFAB = path.combine("Prefabs", "UI", "Family", "ChildIcon.prefab"),
    CHILD_SELECTED_ICON_NAME = "ChildSelectedIcon",
    CHILD_NAME_NAME = "ChildName",
}

---------------------------------------------------------------------------------
local function showChildStats(eventArgs, caller, self)
    self._statsDialog:updateUI()
    self._statsDialog:show()
end

---------------------------------------------------------------------------------
local function hideChildStats(eventArgs, caller, self)
    self._statsDialog:hide()
end

---------------------------------------------------------------------------------
local function onChildSelectedChanged(eventArgs, child, self)
    self:updateSelectionUI()
end

---------------------------------------------------------------------------------
function ChildIcon:new(familyPanel, child)
    local familyPanelStackPanel = familyPanel:findComponent("StackPanel")
    local childPrefab = Resources.loadPrefab(self.CHILD_ICON_PREFAB)
    local childInstance = childPrefab:instantiate(familyPanel:getScreen())
    childInstance:setParent(familyPanel)
    childInstance:setName(child:getName())
    familyPanelStackPanel:addChild(childInstance);

    local childInteractionHandler = childInstance:findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnEnterCallback(showChildStats, self)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildStats, self)

    local childName = childInstance:findChildGameObject(self.CHILD_NAME_NAME)
    childName:findComponent("TextRenderer"):setText(child:getName())
    
    child:subscribeOnSelectedChangedCallback(onChildSelectedChanged, self)

    self.child = child
    self.gameObject = childInstance
    self.selectedIcon = childInstance:findChildGameObject(self.CHILD_SELECTED_ICON_NAME)
    self._statsDialog = Class.new(ChildStatsDialog, childInstance, child)
    self._statsDialog:hide()
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
    local childSelected = self.child:isSelected()
    local animator = self.gameObject:findComponent("Animator")

    if childSelected then
        animator:play()
    else
        animator:stop()
    end

    self.selectedIcon:setShouldRender(childSelected)
end

return ChildIcon