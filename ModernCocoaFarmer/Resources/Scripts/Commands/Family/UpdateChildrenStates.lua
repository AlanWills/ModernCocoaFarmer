local LeaveChild = require 'Commands.Locations.LeaveChild'

local UpdateChildrenStates = {}

---------------------------------------------------------------------------------
function UpdateChildrenStates:execute(commandManager)
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
                child:die()
            elseif child:canGraduate() then
                child:graduate()
            end
        end
    end
end

return UpdateChildrenStates