local Class = require 'OOP.Class'
local ShowLocationDialog = require 'Commands.UI.Locations.ShowLocationDialog'

local LocationIcon = 
{
    CHILD_WALKING_PREFAB_PATH = path.combine("Prefabs", "Gameplay", "Family", "ChildWalkingToLocation.prefab"),
    LOCATION_PROGRESS_PREFAB_PATH = path.combine("Prefabs", "UI", "Locations", "LocationProgress.prefab"),
    ICON_NAME = "Icon",
    PROGRESS_STACK_PANEL_NAME = "ProgressStackPanel",
    CONSTANTS_NAME = "Constants",
    CHILD_NAME_KEY_NAME = "ChildNameKey",
    CHILD_TIME_KEY_NAME = "ChildTimeKey",
    LOCATION_COMPLETION_TIME_KEY_NAME = "LocationCompletionTimeKey",
}

---------------------------------------------------------------------------------
local function onIconClicked(caller, self)
    self._commandManager:execute(ShowLocationDialog, self._locationName)
    
    local icon = self._gameObject:findChild(self.ICON_NAME)
    icon:findComponent("AudioSource"):play()
end

----------------------------------------------------------------------------------------
local function onChildSentCallback(child, self)
    --self:addChildWalking("Home", self._locationName)
    self:addChildLocationProgress(child)
end

----------------------------------------------------------------------------------------
local function onChildLeftCallback(child, self)
    --self:addChildWalking(self._locationName, "Home")
    self:removeChildLocationProgress(child)
end

---------------------------------------------------------------------------------
function LocationIcon:new(commandManager, location, gameObject)
    self._commandManager = commandManager
    self._locationName = location:getName()
    self._gameObject = gameObject
    self._locationProgressBars = {}

    local icon = self._gameObject:findChild(self.ICON_NAME)
    icon:findComponent("MouseInteractionHandler"):subscribeOnLeftButtonUpCallback(onIconClicked, self)

    self._locationProgressStackPanel = icon:findChild(self.PROGRESS_STACK_PANEL_NAME):findComponent("StackPanel")

    location:subscribeOnChildSentCallback(onChildSentCallback, self)
    location:subscribeOnChildLeftCallback(onChildLeftCallback, self)

    for childIndex = 0, (commandManager.familyManager:getChildCount() - 1) do
        local child = commandManager.familyManager:getChild(childIndex)
            
        if child:getCurrentLocation() == self._locationName then
            self:addChildLocationProgress(child)    
        end
    end
end

----------------------------------------------------------------------------------------
local function onLeftButtonUp(caller, extraArgs)
    extraArgs.callback(extraArgs.locationIcon, extraArgs.extraArgs)
end

----------------------------------------------------------------------------------------
function LocationIcon:addChildWalking(from, to)
    local childWalkingPrefab = Resources.loadPrefab(LocationIcon.CHILD_WALKING_PREFAB_PATH)
    local childWalkingInstance = childWalkingPrefab:instantiate()
    childWalkingInstance:setParent(self._gameObject)

    local childWalking = childWalkingInstance:findComponent("ChildWalkingToLocationController")
    childWalkingInstance:getTransform():setWorldTranslation(GameObject.find(from):getTransform():getWorldTranslation())
    childWalking:setLocation(GameObject.find(to):getTransform():getWorldTranslation())
    childWalking:setSpeed(100)
end

----------------------------------------------------------------------------------------
function LocationIcon:addChildLocationProgress(child)
    local locationProgressPrefab = Resources.loadPrefab(self.LOCATION_PROGRESS_PREFAB_PATH)
    local locationProgressGameObject = locationProgressPrefab:instantiate()
    self._locationProgressBars[child:getName()] = locationProgressGameObject
    self._locationProgressStackPanel:addChild(locationProgressGameObject)

    local constantsGameObject = locationProgressGameObject:findChild(self.CONSTANTS_NAME)
    local childNameKeyGameObject = constantsGameObject:findChild(self.CHILD_NAME_KEY_NAME)
    local childTimeKeyGameObject = constantsGameObject:findChild(self.CHILD_TIME_KEY_NAME)
    local locationTimeKeyGameObject = constantsGameObject:findChild(self.LOCATION_COMPLETION_TIME_KEY_NAME)

    childNameKeyGameObject:findComponent("Constant"):setValue(FamilyDataSources.CHILDREN .. "." .. child:getName() .. "." .. FamilyDataSources.CHILD_NAME)
    childTimeKeyGameObject:findComponent("Constant"):setValue(FamilyDataSources.CHILDREN .. "." .. child:getName() .. "." .. FamilyDataSources.TIME_AT_LOCATION)
    locationTimeKeyGameObject:findComponent("Constant"):setValue(LocationsDataSources.LOCATIONS .. "." .. self._locationName .. "." .. LocationsDataSources.DAYS_TO_COMPLETE)
end

----------------------------------------------------------------------------------------
function LocationIcon:removeChildLocationProgress(child)
    local locationProgress = self._locationProgressBars[child:getName()]
    self._locationProgressStackPanel:removeChild(locationProgress.gameObject)

    locationProgress.gameObject:destroy()
    self._locationProgressBars[child:getName()] = nil
end

return LocationIcon
