local ChildStatsDialog = require 'UI.Family.ChildStatsDialog'

---------------------------------------------------------------------------------
local ChildIcon =
{
    CHILD_ICON_PREFAB = path.combine("Prefabs", "UI", "Family", "ChildIcon.prefab"),
    CHILD_SELECTED_ICON_NAME = "ChildSelectedIcon",
    CHILD_NAME_NAME = "ChildName",
    ON_SELECTED_CHANGED_CALLBACK_NAME = "ChildIcon_OnSelectedChanged"
}

---------------------------------------------------------------------------------
local function showChildInformation(eventArgs, caller)
    local statsDialog = ChildStatsDialog.show(caller:getScreen(), ChildInformation.create("Test"))
    statsDialog:setParent(caller);
    statsDialog:getTransform():translate(0, -240)
end

---------------------------------------------------------------------------------
local function hideChildInformation(eventArgs, caller)
    local statsDialog = caller:findChildGameObject("ChildStatsBackground")
    statsDialog:die()
end

---------------------------------------------------------------------------------
local function onChildSelectedChanged(childIcon, child, isNowSelected)
    childIcon:updateSelectionUI(isNowSelected)
end

---------------------------------------------------------------------------------
function ChildIcon:new(familyPanel, child)
    local familyPanelStackPanel = familyPanel:findComponent("StackPanel")
    local childPrefab = Resources.loadPrefab(self.CHILD_ICON_PREFAB)
    local childInstance = childPrefab:instantiate(familyPanel:getScreen())
    childInstance:setParent(familyPanel)
    childInstance:setName(child.name)
    familyPanelStackPanel:addChild(childInstance);

    local childInteractionHandler = childInstance:findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnEnterCallback(showChildInformation)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildInformation)

    local childName = childInstance:findChildGameObject(self.CHILD_NAME_NAME)
    childName:findComponent("TextRenderer"):setText(child.name)
    
    child:subscribeOnSelectedChangedCallback(self.ON_SELECTED_CHANGED_CALLBACK_NAME, onChildSelectedChanged, self)

    self.child = child
    self.gameObject = childInstance
    self.selectedIcon = childInstance:findChildGameObject(self.CHILD_SELECTED_ICON_NAME)
end

---------------------------------------------------------------------------------
function ChildIcon:updateSelectionUI(isNowSelected)
    self.selectedIcon:setShouldRender(isNowSelected)
end

return ChildIcon