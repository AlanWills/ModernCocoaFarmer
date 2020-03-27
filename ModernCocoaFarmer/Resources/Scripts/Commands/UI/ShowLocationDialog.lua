local ShowModalDialog = require 'Commands.UI.ShowModalDialog'
local LocationDialog = require 'UI.Locations.LocationDialog'
local Class = require 'OOP.Class'
local Algorithm = require 'Containers.Algorithm'

local ShowLocationDialog = Class.inheritsFrom(ShowModalDialog)

---------------------------------------------------------------------------------
function ShowLocationDialog:new(...)
    ShowModalDialog.new(self, LocationDialog, ...)
end

---------------------------------------------------------------------------------
function ShowLocationDialog:execute(commandManager)
    local selectedChild = nil
    
    if commandManager.familyManager:hasSelectedChild() then
        selectedChild = commandManager.familyManager:getSelectedChild()
        log("Family Manager has " .. selectedChild:getName() .. " selected for Location Dialog")
    end

    -- Push an extra argument
    self._args[Algorithm.tablelength(self._args)] = selectedChild

    ShowModalDialog.execute(self, commandManager)
end

return ShowLocationDialog