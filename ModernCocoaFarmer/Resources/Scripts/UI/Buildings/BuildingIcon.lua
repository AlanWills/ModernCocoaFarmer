local Class = require 'OOP.Class'
local InteractableBuildingDialog = require "UI.InteractableBuildingDialog"

local BuildingIcon = 
{
        ICON_NAME = "Icon"
}

---------------------------------------------------------------------------------
function BuildingIcon:new(building, parent)
    self._building = building

    local buildingPrefab = Resources.loadPrefab(building:getPrefab())
    self._gameObject = buildingPrefab:instantiate(parent:getScreen())
    self._gameObject:setParent(parent)
end

----------------------------------------------------------------------------------------
local function onLeftButtonUp(eventArgs, caller, extraArgs)
    extraArgs.callback(extraArgs.buildingIcon, extraArgs.extraArgs)
end

----------------------------------------------------------------------------------------
function BuildingIcon:subscribeIconClickedCallback(callback, extraArgs)
    local icon = self._gameObject:findChildGameObject(self.ICON_NAME)
    icon:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(onLeftButtonUp, { callback = callback, buildingIcon = self, extraArgs = extraArgs })
end

----------------------------------------------------------------------------------------
function BuildingIcon:showDetails(selectedChild)
    Class.new(InteractableBuildingDialog, self._gameObject:getScreen(), self._building, selectedChild)
end

return BuildingIcon