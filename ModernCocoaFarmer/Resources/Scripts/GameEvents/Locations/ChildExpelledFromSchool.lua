local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local LeaveChild = require 'Commands.Locations.LeaveChild'
local SendNotification = require 'Commands.Notifications.SendNotification'

local ChildExpelledFromSchool = {}

---------------------------------------------------------------------------------
ChildExpelledFromSchool.NAME = "ChildExpelledFromSchool"
ChildExpelledFromSchool.CHILD_HAPPINESS_THRESHOLD = 25
ChildExpelledFromSchool.DAY_TO_TRIGGER = 15
ChildExpelledFromSchool.PERIOD = GameEventPeriod.EVERY_DAY
ChildExpelledFromSchool.ICON_PATH = path.combine("Textures", "UI", "Utility", "WhitePixel.png")

---------------------------------------------------------------------------------
function ChildExpelledFromSchool.isValidForExpulsion(child)
    return child:getHappiness() <= ChildExpelledFromSchool.CHILD_HAPPINESS_THRESHOLD and
           child:isAtLocation() and 
           child:getCurrentLocation() == "School"
end

---------------------------------------------------------------------------------
function ChildExpelledFromSchool.canTrigger(commandManager)
    if commandManager.timeManager:getCurrentDay() ~= ChildExpelledFromSchool.DAY_TO_TRIGGER then
        return false
    end
    
    -- Check at least one child has a happiness less than or equal to the threshold and is at the school
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if ChildExpelledFromSchool.isValidForExpulsion(child) then
            return true
        end
    end

    return false
end

---------------------------------------------------------------------------------
function ChildExpelledFromSchool.trigger(commandManager)
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if ChildExpelledFromSchool.isValidForExpulsion(child) then
            commandManager:execute(LeaveChild, child:getCurrentLocation(), child:getName())
            child:setEducation(0)
            break
        end
    end

    commandManager:execute(SendNotification, "Child Expelled", "TODO", ChildExpelledFromSchool.ICON_PATH)
end

return ChildExpelledFromSchool