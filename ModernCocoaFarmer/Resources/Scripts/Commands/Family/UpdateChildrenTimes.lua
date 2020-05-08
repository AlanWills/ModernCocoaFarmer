local UpdateChildrenTimes = {}

---------------------------------------------------------------------------------
function UpdateChildrenTimes:new(elapsedWorldTime)  
    self._elapsedWorldTime = elapsedWorldTime
end

---------------------------------------------------------------------------------
function UpdateChildrenTimes:execute(commandManager)
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isAtLocation() then
            child:incrementTimeAtLocation(self._elapsedWorldTime)
        end
    end
end

return UpdateChildrenTimes