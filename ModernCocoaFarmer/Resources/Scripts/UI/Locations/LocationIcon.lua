local Class = require 'OOP.Class'
local LocationDialog = require 'UI.Locations.LocationDialog'
local LocationProgress = require 'UI.Locations.LocationProgress'

local LocationIcon = 
{
    ICON_NAME = "Icon",
    LOCATION_PROGRESS_STACK_PANEL = "LocationProgessStackPanel"
    LOCATION_PROGRESS_PREFAB_PATH = path.combine("Prefabs", "UI", "Locations", "LocationProgress.prefab"),
    CHILD_NAME_TEXT = "ChildNameText",
}

----------------------------------------------------------------------------------------
local function onChildSentCallback(eventArgs, child, self)
    self:addChildLocationProgress(child)
end

----------------------------------------------------------------------------------------
local function onChildLeftCallback(eventArgs, child, self)
    self:removeChildLocationProgress(child)
end

---------------------------------------------------------------------------------
function LocationIcon:new(location, parent)
    self._location = location
    self._locationProgressBars = {}
    self._locationProgressPrefab = Resources.loadPrefab(self.LOCATION_PROGRESS_PREFAB_PATH)

    local locationPrefab = Resources.loadPrefab(location:getPrefab())
    self._gameObject = locationPrefab:instantiate(parent:getScreen())
    self._gameObject:setParent(parent)
    self._locationProgressStackPanel = self._gameObject:findChildGameObject(self.LOCATION_PROGRESS_STACK_PANEL):findComponent("StackPanel")

    location:subscribeOnChildSentCallback(onChildSentCallback, self)
    location:subscribeOnChildLeftCallback(onChildLeftCallback, self)
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
    Class.new(LocationDialog, self._gameObject:getScreen(), self._location, selectedChild)
end

----------------------------------------------------------------------------------------
function LocationIcon:addChildLocationProgress(child)
    local locationProgress = Class.new(LocationProgress, child, self._gameObject:getScreen())--self._locationProgressPrefab:instantiate(self._gameObject:getScreen())
    locationProgress:findChildGameObject(SELF.CHILD_NAME_TEXT):findComponent("TextRenderer"):setText(child:getName())

    self._locationProgressBars[child:getName()] = locationProgress
    self._locationProgressStackPanel:addChild(locationProgress.gameObject)
end

----------------------------------------------------------------------------------------
function LocationIcon:removeChildLocationProgress(child)
    local locationProgress = self._locationProgressBars[child:getName()]
    self._locationProgressStackPanel:removeChild(locationProgress.gameObject)

    locationProgress.gameObject:die()
    self._locationProgressBars[child:getName()] = nil
end

----------------------------------------------------------------------------------------
function LocationIcon:updateUI()
    for k, locationProgress in pairs(self._locationProgressBars)
        locationProgress:updateUI()
    end
end

return LocationIcon
