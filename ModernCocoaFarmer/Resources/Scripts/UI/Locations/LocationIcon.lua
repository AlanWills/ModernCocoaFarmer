local Class = require 'OOP.Class'
local LocationDialog = require 'UI.Locations.LocationDialog'
local LocationProgress = require 'UI.Locations.LocationProgress'
local ModalDialogManager = require 'UI.Dialogs.ModalDialogManager'

local LocationIcon = 
{
    ICON_NAME = "Icon",
    PROGRESS_STACK_PANEL_NAME = "ProgressStackPanel",
    CHILD_WALKING_PREFAB_PATH = path.combine("Prefabs", "Gameplay", "Family", "ChildWalkingToLocation.prefab"),
}

----------------------------------------------------------------------------------------
local function onChildSentCallback(child, self)
    self:addChildWalking("Home", self._location:getName())
    self:addChildLocationProgress(child)
end

----------------------------------------------------------------------------------------
local function onChildLeftCallback(child, self)
    self:addChildWalking(self._location:getName(), "Home")
    self:removeChildLocationProgress(child)
end

---------------------------------------------------------------------------------
function LocationIcon:new(location, parent)
    self._location = location
    self._locationProgressBars = {}

    local locationPrefab = Resources.loadPrefab(location:getPrefab())
    self._gameObject = locationPrefab:instantiate()
    self._gameObject:setParent(parent)

    local icon = self._gameObject:findChild(self.ICON_NAME)
    self._locationProgressStackPanel = icon:findChild(self.PROGRESS_STACK_PANEL_NAME):findComponent("StackPanel")

    location:subscribeOnChildSentCallback(onChildSentCallback, self)
    location:subscribeOnChildLeftCallback(onChildLeftCallback, self)
end

----------------------------------------------------------------------------------------
local function onLeftButtonUp(caller, extraArgs)
    extraArgs.callback(extraArgs.locationIcon, extraArgs.extraArgs)
end

----------------------------------------------------------------------------------------
function LocationIcon:subscribeIconClickedCallback(callback, extraArgs)
    local icon = self._gameObject:findChild(self.ICON_NAME)
    icon:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(onLeftButtonUp, { callback = callback, locationIcon = self, extraArgs = extraArgs })
end

----------------------------------------------------------------------------------------
function LocationIcon:showDetails(selectedChild)
    --Class.new(LocationDialog, self._location, selectedChild)
    ModalDialogManager.instance:showDialog(LocationDialog, self._location, selectedChild)
end

----------------------------------------------------------------------------------------
function LocationIcon:addChildWalking(from, to)
    local childWalkingPrefab = Resources.loadPrefab(LocationIcon.CHILD_WALKING_PREFAB_PATH);
    local childWalkingInstance = childWalkingPrefab:instantiate();
    local childWalking = childWalkingInstance:findComponent("ChildWalkingToLocationController")
    childWalkingInstance:getTransform():setWorldTranslation(GameObject.find(from):getTransform():getWorldTranslation())
    childWalking:setLocation(GameObject.find(to):getTransform():getWorldTranslation())
    childWalking:setSpeed(100)
end

----------------------------------------------------------------------------------------
function LocationIcon:addChildLocationProgress(child)
    local locationProgress = Class.new(LocationProgress, child:getName())
    self._locationProgressBars[child:getName()] = locationProgress
    self._locationProgressStackPanel:addChild(locationProgress.gameObject)
end

----------------------------------------------------------------------------------------
function LocationIcon:removeChildLocationProgress(child)
    local locationProgress = self._locationProgressBars[child:getName()]
    self._locationProgressStackPanel:removeChild(locationProgress.gameObject)

    locationProgress.gameObject:destroy()
    self._locationProgressBars[child:getName()] = nil
end

----------------------------------------------------------------------------------------
function LocationIcon:updateUI()
    local locationDaysToComplete = self._location:getDaysToComplete()
    for childName, locationProgress in pairs(self._locationProgressBars) do
        local childDaysSpent = self._location:getChildTime(childName)
        locationProgress:updateUI((100 * childDaysSpent) / locationDaysToComplete)
    end
end

return LocationIcon
