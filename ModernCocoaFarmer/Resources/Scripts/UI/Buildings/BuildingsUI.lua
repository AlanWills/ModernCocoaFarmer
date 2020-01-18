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
local function onBuildingIconClicked(buildingIcon, self)
    local selectedChild = nil
    
    if self._familyManager:hasSelectedChild() then
        selectedChild = self._familyManager:getSelectedChild()
    end

    buildingIcon:showDetails(selectedChild)
end

---------------------------------------------------------------------------------
function BuildingsUI:new(buildingsManager, familyManager, gameObject)
    self._buildingIcons = {}
    self._familyManager = familyManager

    for k, v in pairs(self.BuildingNames) do
        local building = buildingsManager:getBuilding(v)
        
        if building == nil then
            log("Error getting building " .. v)
        else
            local buildingIcon = Class.new(BuildingIcon, building, gameObject)
            buildingIcon:subscribeIconClickedCallback(onBuildingIconClicked, self)

            self._buildingIcons[v] = buildingIcon
        end
    end
end

return BuildingsUI