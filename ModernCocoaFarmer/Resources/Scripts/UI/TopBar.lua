local csd = require 'UI.Family.ChildStatsDialog'

local topBar = {}

---------------------------------------------------------------------------------
topBar.TOP_BAR_NAME = "TopBar"
topBar.FAMILY_PANEL_NAME = "FamilyPanelStackPanel"
topBar.CHILD_ICON_PREFAB = path.combine("Prefabs", "Gameplay", "Family", "ChildIcon.prefab")
topBar.CHILD_SELECTED_ICON_NAME = "ChildSelectedIcon"
topBar.CHILD_NAME_NAME = "ChildName"
topBar.MENU_BUTTON_NAME = "MenuButton"

---------------------------------------------------------------------------------
local function selectChild(eventArgs, caller)
    local outline = caller:findChildGameObject(topBar.CHILD_SELECTED_ICON_NAME)
    outline:setShouldRender(true)

    -- Update this to hide all the other children
end

---------------------------------------------------------------------------------
local function showChildInformation(eventArgs, caller)
    local statsDialog = csd.show(caller:getScreen(), ChildInformation.create("Test"))
    statsDialog:setParent(caller);
    statsDialog:getTransform():translate(0, -240)
end

---------------------------------------------------------------------------------
local function hideChildInformation(eventArgs, caller)
    local statsDialog = caller:findChildGameObject("ChildStatsBackground")
    statsDialog:die()
end

---------------------------------------------------------------------------------
function topBar.initialize(screen)
    -- Set up family UI being populated
    local familyPanel = screen:findGameObject(topBar.FAMILY_PANEL_NAME)
    local familyPanelStackPanel = familyPanel:findComponent("StackPanel")

    -- Refactor this out into a child icon lua module?
    local childPrefab = Resources.loadPrefab(topBar.CHILD_ICON_PREFAB)
    local childInstance = childPrefab:instantiate(screen);
    childInstance:setParent(familyPanel);
    familyPanelStackPanel:addChild(childInstance);

    local childInteractionHandler = childInstance:findComponent("MouseInteractionHandler")
    childInteractionHandler:subscribeOnLeftButtonClickedCallback(selectChild)
    childInteractionHandler:subscribeOnEnterCallback(showChildInformation)
    childInteractionHandler:subscribeOnLeaveCallback(hideChildInformation)

    local childName = childInstance:findChildGameObject(topBar.CHILD_NAME_NAME)
    childName:findComponent("TextRenderer"):setText("Child Name")
    
    -- Set up menu button loading menu prefab here
end

return topBar