local UpdateChildrenTimes = {}

---------------------------------------------------------------------------------
function UpdateChildrenTimes:new(elapsedWorldTime)  
    self._elapsedWorldTime = elapsedWorldTime
end

---------------------------------------------------------------------------------
function UpdateChildrenTimes:execute(commandManager)
    log("Updating children times")
    local familyManager = commandManager.familyManager

    for childIndex = 0, (familyManager:getChildCount() - 1) do
        local child = familyManager:getChild(childIndex)

        if child:isAtLocation() then
            log("Updating " .. child:getName() .. " time at " .. child:getCurrentLocation())
            child:incrementTimeAtLocation(self._elapsedWorldTime)
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