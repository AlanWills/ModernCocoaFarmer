local Class = require 'OOP.Class'
local LocationIcon = require 'UI.Locations.LocationIcon'

local LocationsUI = {}

LocationsUI.LocationNames = 
{
    FARM = "Cocoa Farm",
    HOME = "Home",
    HOSPITAL = "Hospital",
    MARKET = "Market",
    MOSQUE = "Mosque",
    SCHOOL = "School",
    WELL = "Well",
}

---------------------------------------------------------------------------------
local function onLocationIconClicked(locationIcon, self)
    local selectedChild = nil
    
    if self._familyManager:hasSelectedChild() then
        selectedChild = self._familyManager:getSelectedChild()
    end

    locationIcon:showDetails(selectedChild)
end

---------------------------------------------------------------------------------
function LocationsUI:new(locationsManager, familyManager, gameObject)
    self._locationIcons = {}
    self._familyManager = familyManager

    for k, v in pairs(self.LocationNames) do
        local location = locationsManager:getLocation(v)
        
        if location == nil then
            log("Error getting location " .. v)
        else
            local locationIcon = Class.new(LocationIcon, location, gameObject)
            locationIcon:subscribeIconClickedCallback(onLocationIconClicked, self)

            self._locationIcons[v] = locationIcon
        end
    end
end

---------------------------------------------------------------------------------
function LocationsUI:updateUI()
    for k, locationIcon in pairs(self._locationIcons) do
        locationIcon:updateUI()
    end
end

return LocationsUI
