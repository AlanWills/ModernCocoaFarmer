local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local LeaveChild = require 'Commands.Locations.LeaveChild'
local SendNotification = require 'Commands.Notifications.SendNotification'

---------------------------------------------------------------------------------
local CheckForChildrenLeaving = {}
CheckForChildrenLeaving.CHILD_TRAFFICKED_ICON_PATH = path.combine("Textures", "UI", "ChildIcons", "ChildDead.png")
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

                if location:getName() == "Farm" then
                    if math.random() > child:getSafety() then
                        -- Child is trafficked
                        child:die()

                        commandManager:execute(
                            SendNotification,
                            "Child Trafficked...",
                            "The unthinkable has happened.  On the return journey from the Cocoa Farm " .. child:getName() .. " was taken.  You pray you will see them again, but deep down you know you won't.",
                            CheckForChildrenLeaving.CHILD_TRAFFICKED_ICON_PATH)
                    end
                end
            end
        end
    end
end

return CheckForChildrenLeaving