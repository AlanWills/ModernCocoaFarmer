local LeaveChild = require 'Commands.Locations.LeaveChild'
local SendNotification = require 'Commands.Notifications.SendNotification'

local UpdateChildrenStates = {}
UpdateChildrenStates.CHILD_DECEASED_ICON_PATH = path.combine("Textures", "UI", "ChildIcons", "ChildDead.png")
UpdateChildrenStates.CHILD_GRADUATED_ICON_PATH = path.combine("Textures", "UI", "ChildIcons", "ChildGraduated.png")

---------------------------------------------------------------------------------
function UpdateChildrenStates:execute(commandManager)
    log("Updating children states")
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isActivated() then
            local isAtLocation = child:isAtLocation()
            local needsToLeaveLocation = child:canDie() or child:canGraduate()

            if isAtLocation and needsToLeaveLocation then
                commandManager:execute(LeaveChild, child:getCurrentLocation(), child:getName())
            end
            
            if child:canDie() then
                log(child:getName() .. " is now dead")
                child:die()

                commandManager:execute(
                    SendNotification,
                    "A Child Dies...",
                    "After lingering on death's door, " .. child:getName() .. " has finally stepped over.  Your family bitterly rues their passing.",
                    UpdateChildrenStates.CHILD_DECEASED_ICON_PATH)
            elseif child:canGraduate() then
                log(child:getName() .. " is now graduated")
                child:graduate()

                commandManager:execute(
                    SendNotification,
                    "Graduation Day!",
                    "School is never easy, but " .. child:getName() .. " has successfully graduated.  Their education gives them hope for a better life.",
                    UpdateChildrenStates.CHILD_GRADUATED_ICON_PATH)
            end
        end
    end
end

return UpdateChildrenStates