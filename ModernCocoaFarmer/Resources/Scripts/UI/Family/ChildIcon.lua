local Class = require 'OOP.Class'
local ChildStatsDialog = require 'UI.Family.ChildStatsDialog'

---------------------------------------------------------------------------------
local ChildIcon = Class.declare()
ChildIcon.CHILD_ICON_PREFAB = path.combine("Prefabs", "Gameplay", "Family", "ChildIcon.prefab")
ChildIcon.CHILD_SELECTED_ICON_NAME = "ChildSelectedIcon"
ChildIcon.CHILD_NAME_NAME = "ChildName"
ChildIcon.ON_SELECTED_CHANGED_CALLBACK_NAME = "ChildIcon_OnSelectedChanged"

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
local function onChildSelectedChanged(child, isNowSelected, childIcon)
    childIcon:updateSelectionUI(isNowSelected)
end

---------------------------------------------------------------------------------
function ChildIcon.new(familyPanel, child)
    local childIcon = Class.new(ChildIcon)
    local familyPanelStackPanel = familyPanel:findComponent("StackPanel")
    local childPrefab = Resources.loadPrefab(ChildIcon.CHILD_ICON_PREFAB)
    local childInstance = childPrefab:instantiate(familyPanel:getScreen())
    childInstance:setParent(familyPanel)
    childInstance:setName(child.name)
    familyPanelStackPanel:addChild(childInstance);

    local childInteractionHandler = childInstance:findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnEnterCallback(showChildInformation)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildInformation)

    local childName = childInstance:findChildGameObject(ChildIcon.CHILD_NAME_NAME)
    childName:findComponent("TextRenderer"):setText(child.name)
    
    child:subscribeOnSelectedChangedCallback(ChildIcon.ON_SELECTED_CHANGED_CALLBACK_NAME, onChildSelectedChanged, childIcon)

    childIcon.child = child
    childIcon.gameObject = childInstance
    childIcon.selectedIcon = childInstance:findChildGameObject(ChildIcon.CHILD_SELECTED_ICON_NAME)

    return childIcon
end

---------------------------------------------------------------------------------
function ChildIcon:updateSelectionUI(isNowSelected)
    self.selectedIcon:setShouldRender(isNowSelected)
end

return ChildIcon