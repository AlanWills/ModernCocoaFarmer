local ChildStatsDialog = require 'UI.Family.ChildStatsDialog'

local childIcon = {}

---------------------------------------------------------------------------------
childIcon.CHILD_ICON_PREFAB = path.combine("Prefabs", "Gameplay", "Family", "ChildIcon.prefab")
childIcon.CHILD_SELECTED_ICON_NAME = "ChildSelectedIcon"
childIcon.CHILD_NAME_NAME = "ChildName"

---------------------------------------------------------------------------------
local function selectChild(eventArgs, caller)
    local outline = caller:findChildGameObject(childIcon.CHILD_SELECTED_ICON_NAME)
    outline:setShouldRender(true)

    -- Update this to hide all the other children
end

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
function childIcon.initialize(familyPanel, child)
    local familyPanelStackPanel = familyPanel:findComponent("StackPanel")
    local childPrefab = Resources.loadPrefab(childIcon.CHILD_ICON_PREFAB)
    local childInstance = childPrefab:instantiate(familyPanel:getScreen());
    childInstance:setParent(familyPanel);
    familyPanelStackPanel:addChild(childInstance);

    local childInteractionHandler = childInstance:findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnLeftButtonClickedCallback(selectChild)
    childInteractionHandler:subscribeOnEnterCallback(showChildInformation)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildInformation)

    local childName = childInstance:findChildGameObject(childIcon.CHILD_NAME_NAME)
    childName:findComponent("TextRenderer"):setText(child.name)

    return childInstance
end

return childIcon