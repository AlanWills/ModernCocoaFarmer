local Class = require 'OOP.Class'
local BuildingIcon = require 'UI.Buildings.BuildingIcon'

local BuildingsUI = {}

BuildingsUI.BuildingNames = 
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
function BuildingsUI:new(buildingsManager, gameObject)
    self._buildingIcons = {}

    for k, v in pairs(self.BuildingNames) do
        local building = buildingsManager:getBuilding(v)
        
        if building == nil then
            log("Error getting building " .. v)
        else
            self._buildingIcons[v] = Class.new(BuildingIcon, building, gameObject)
        end
    end
end

return BuildingsUI