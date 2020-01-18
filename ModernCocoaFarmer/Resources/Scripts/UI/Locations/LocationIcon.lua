local Class = require 'OOP.Class'
local InteractableLocationDialog = require "UI.InteractableLocationDialog"

local LocationIcon = 
{
        ICON_NAME = "Icon"
}

---------------------------------------------------------------------------------
function LocationIcon:new(location, parent)
    self._location = location

    local locationPrefab = Resources.loadPrefab(location:getPrefab())
    self._gameObject = locationPrefab:instantiate(parent:getScreen())
    self._gameObject:setParent(parent)
end

----------------------------------------------------------------------------------------
local function onLeftButtonUp(eventArgs, caller, extraArgs)
    extraArgs.callback(extraArgs.locationIcon, extraArgs.extraArgs)
end

----------------------------------------------------------------------------------------
function LocationIcon:subscribeIconClickedCallback(callback, extraArgs)
    local icon = self._gameObject:findChildGameObject(self.ICON_NAME)
    icon:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(onLeftButtonUp, { callback = callback, locationIcon = self, extraArgs = extraArgs })
end

----------------------------------------------------------------------------------------
function LocationIcon:showDetails(selectedChild)
    Class.new(InteractableLocationDialog, self._gameObject:getScreen(), self._location, selectedChild)
end

return LocationIcon
