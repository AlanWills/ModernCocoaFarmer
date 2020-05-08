local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local LeaveChild = require 'Commands.Locations.LeaveChild'

local CheckForChildrenLeaving = {}

---------------------------------------------------------------------------------
CheckForChildrenLeaving.NAME = "CheckForChildrenLeaving"
CheckForChildrenLeaving.PERIOD = GameEventPeriod.EVERY_DAY

---------------------------------------------------------------------------------
function CheckForChildrenLeaving.trigger(commandManager)
    local locationsManager = commandManager.locationsManager
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isAtLocation() then
            local location = locationsManager:findLocation(child:getCurrentLocation())

            if child:getTimeAtLocation() >= location:getDaysToComplete() then
                commandManager:execute(LeaveChild, child:getCurrentLocation(), child:getName())
                -- N.B. This is where we can do notifications for children leaving and leaving effects
            end
        end
    end
end

return CheckForChildrenLeaving