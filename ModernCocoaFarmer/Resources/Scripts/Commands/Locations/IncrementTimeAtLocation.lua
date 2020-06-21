local IncrementTimeAtLocation = {}

---------------------------------------------------------------------------------
function IncrementTimeAtLocation:new(childName, timeToAdd)
    self._childName = childName
    self._timeToAdd = timeToAdd
end

---------------------------------------------------------------------------------
function IncrementTimeAtLocation:execute(commandManager)
    local child = commandManager.familyManager:findChild(self._childName)

    if child == nil then
        log("[IncrementTimeAtLocation]  Could not find child " .. self._childName)
        return
    end

    log("Adding " .. tostring(self._timeToAdd) .. " time to ".. self._childName .. " time at " .. child:getCurrentLocation())
    child:incrementTimeAtLocation(self._timeToAdd)
end

---------------------------------------------------------------------------------
function IncrementTimeAtLocation.parseArgs(args)
    if #args < 1 then
        return nil, "Missing child name argument"
    end

    if #args < 2 then
        return nil, "Missing time to add argument"
    end

    return args
end

return IncrementTimeAtLocation