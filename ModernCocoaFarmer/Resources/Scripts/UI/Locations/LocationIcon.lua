local Class = require 'OOP.Class'
local LocationProgress = require 'UI.Locations.LocationProgress'
local ShowLocationDialog = require 'Commands.UI.Locations.ShowLocationDialog'

local LocationIcon = 
{
    ICON_NAME = "Icon",
    PROGRESS_STACK_PANEL_NAME = "ProgressStackPanel",
    CHILD_WALKING_PREFAB_PATH = path.combine("Prefabs", "Gameplay", "Family", "ChildWalkingToLocation.prefab"),
}

---------------------------------------------------------------------------------
local function onIconClicked(caller, self)
    self._commandManager:execute(ShowLocationDialog, self._dataStore, self._locationName)
    
    local icon = self._gameObject:findChild(self.ICON_NAME)
    icon:findComponent("AudioSource"):play()
end

----------------------------------------------------------------------------------------
local function onChildSentCallback(child, self)
    self:addChildWalking("Home", self._locationName)
    self:addChildLocationProgress(child)
end

----------------------------------------------------------------------------------------
local function onChildLeftCallback(child, self)
    self:addChildWalking(self._locationName, "Home")
    self:removeChildLocationProgress(child)
end

---------------------------------------------------------------------------------
function LocationIcon:new(commandManager, dataStore, location, gameObject)
    self._commandManager = commandManager
    self._dataStore = dataStore
    self._locationName = location:getName()
    self._gameObject = gameObject
    self._locationProgressBars = {}

    local icon = self._gameObject:findChild(self.ICON_NAME)
    icon:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(onIconClicked, self)

    self._locationProgressStackPanel = icon:findChild(self.PROGRESS_STACK_PANEL_NAME):findComponent("StackPanel")

    location:subscribeOnChildSentCallback(onChildSentCallback, self)
    location:subscribeOnChildLeftCallback(onChildLeftCallback, self)
end

----------------------------------------------------------------------------------------
local function onLeftButtonUp(caller, extraArgs)
    extraArgs.callback(extraArgs.locationIcon, extraArgs.extraArgs)
end

----------------------------------------------------------------------------------------
function LocationIcon:addChildWalking(from, to)
    local childWalkingPrefab = Resources.loadPrefab(LocationIcon.CHILD_WALKING_PREFAB_PATH);
    local childWalkingInstance = childWalkingPrefab:instantiate();
    childWalkingInstance:setParent(self._gameObject)

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
    local locationObject = self._dataStore:getObject(LocationsDataSources.LOCATIONS .. "." .. self._locationName)
    local locationDaysToComplete = locationObject:getUnsignedInt(LocationsDataSources.DAYS_TO_COMPLETE)

    for childName, locationProgress in pairs(self._locationProgressBars) do
        local childDaysSpent = locationObject:getUnsignedInt(childName .. "." .. LocationsDataSources.DAYS_AT_LOCATION)
        locationProgress:updateUI((100 * childDaysSpent) / locationDaysToComplete)
    end
end

return LocationIcon
