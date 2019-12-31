local ChildStatsDialog = require 'UI.Family.ChildStatsDialog'

---------------------------------------------------------------------------------
local ChildIcon =
{
    CHILD_ICON_PREFAB = path.combine("Prefabs", "UI", "Family", "ChildIcon.prefab"),
    CHILD_SELECTED_ICON_NAME = "ChildSelectedIcon",
    CHILD_NAME_NAME = "ChildName",
}

---------------------------------------------------------------------------------
local function showChildStats(eventArgs, caller, child)
    local statsDialog = ChildStatsDialog.show(caller:getScreen(), child)
    statsDialog:setParent(caller);
    statsDialog:getTransform():translate(0, -240)
end

---------------------------------------------------------------------------------
local function hideChildStats(eventArgs, caller)
    local statsDialog = caller:findChildGameObject("ChildStatsBackground")
    statsDialog:die()
end

---------------------------------------------------------------------------------
local function onChildSelectedChanged(eventArgs, child, isNowSelected, childIcon)
    childIcon:updateSelectionUI(isNowSelected)
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
    childInteractionHandler:subscribeOnEnterCallback(showChildStats, child)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildStats)

    local childName = childInstance:findChildGameObject(self.CHILD_NAME_NAME)
    childName:findComponent("TextRenderer"):setText(child:getName())
    
    child:subscribeOnSelectedChangedCallback(onChildSelectedChanged, self)

    self.child = child
    self.gameObject = childInstance
    self.selectedIcon = childInstance:findChildGameObject(self.CHILD_SELECTED_ICON_NAME)
end

---------------------------------------------------------------------------------
function ChildIcon:updateSelectionUI(isNowSelected)
    self.selectedIcon:setShouldRender(isNowSelected)
end

return ChildIcon