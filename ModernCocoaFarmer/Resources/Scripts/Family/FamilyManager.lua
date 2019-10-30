local family = {}

---------------------------------------------------------------------------------
family.FAMILY_PANEL_NAME = "FamilyPanelStackPanel"
family.CHILD_ICON_PREFAB = path.combine("Prefabs", "Gameplay", "Family", "ChildIcon.prefab")
family.CHILD_NAME_NAME = "ChildName"

---------------------------------------------------------------------------------
function family.initialize(screen)
    local familyPanel = screen:findGameObject(family.FAMILY_PANEL_NAME)
    local familyPanelStackPanel = familyPanel:findComponent("StackPanel")

    local childPrefab = Resources.loadPrefab(family.CHILD_ICON_PREFAB)
    local childInstance = childPrefab:instantiate(screen);
    childInstance:setParent(familyPanel);
    familyPanelStackPanel:addChild(childInstance);
end

return family

-- Make stack panel script commands
-- Don't forget 'addChild'
-- Unit Test GameObjectScriptCommands setParent