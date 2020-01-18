local InteractableBuildingDialog = require "UI.InteractableBuildingDialog"

local BuildingIcon = {}

----------------------------------------------------------------------------------------
local function iconClicked(e, caller, building)
    InteractableBuildingDialog.show(caller:getScreen(), building);
end

---------------------------------------------------------------------------------
function BuildingIcon:new(building, parent)
    self._building = building

    local buildingPrefab = Resources.loadPrefab(building:getPrefab())
    self._gameObject = buildingPrefab:instantiate(parent:getScreen())
    self._gameObject:setParent(parent);

    local icon = self._gameObject:findChildGameObject("Icon")
    icon:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(iconClicked, self._building)
end

return BuildingIcon