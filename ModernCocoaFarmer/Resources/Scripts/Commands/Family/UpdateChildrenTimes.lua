local UpdateChildrenTimes = {}

---------------------------------------------------------------------------------
function UpdateChildrenTimes:new(timeToAdd)  
    self._timeToAdd = timeToAdd
end

---------------------------------------------------------------------------------
function UpdateChildrenTimes:execute(commandManager)
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isAtLocation() then
            child:incrementTimeAtLocation(self._timeToAdd)
        end
    end
end

---------------------------------------------------------------------------------
function UpdateChildrenTimes.parseArgs(args)
    if #args < 1 then
        return nil, "Missing elapsed time argument"
    end

    args[1] = tonumber(args[1])
    return args
end

return UpdateChildrenTimes