local ShowModalDialog = require 'Commands.UI.ShowModalDialog'
local LocationDialog = require 'UI.Locations.LocationDialog'
local Class = require 'OOP.Class'

local ShowLocationDialog = Class.inheritsFrom(ShowModalDialog)

---------------------------------------------------------------------------------
function ShowLocationDialog:new(...)
    ShowModalDialog.new(self, LocationDialog, ...)
end

---------------------------------------------------------------------------------
function ShowLocationDialog:execute(commandManager)
    ShowModalDialog.execute(self, commandManager)
end

---------------------------------------------------------------------------------
function ShowLocationDialog.parseArgs(args)
    local argCount = #args
    
    if argCount < 1 then
        return nil, "Missing location name argument"
    end

    return args
end

return ShowLocationDialog