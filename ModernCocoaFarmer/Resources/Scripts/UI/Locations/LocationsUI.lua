local LocationIcon = require 'UI.Locations.LocationIcon'
local Class = require 'OOP.Class'

local LocationsUI = {}

---------------------------------------------------------------------------------
function LocationsUI.onLocationActivatedCallback(location, self)
    self:addLocationIcon(location)
end

---------------------------------------------------------------------------------
function LocationsUI:new(commandManager, gameObject)
    self._commandManager = commandManager
    self._gameObject = gameObject
    self._locationIcons = {}

    commandManager.locationsManager:subscribeOnLocationActivatedCallback(LocationsUI.onLocationActivatedCallback, self)
end

---------------------------------------------------------------------------------
function LocationsUI:addLocationIcon(location)
    local locationName = location:getName()
    local locationGameObject = self._gameObject:findChild(locationName)

    if locationGameObject == nil then
        log("Could not find location " .. locationName .. " game object")
        return
    end

    self._locationIcons[locationName] = Class.new(LocationIcon, self._commandManager, location, locationGameObject)
    log("Added location icon for " .. locationName)
end

return LocationsUI
