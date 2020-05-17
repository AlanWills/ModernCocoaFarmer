local DeselectChild = {}

---------------------------------------------------------------------------------
function DeselectChild:new(locationName, childName)
    self._locationName = locationName
    self._childName = childName
end

---------------------------------------------------------------------------------
function DeselectChild:execute(commandManager)
    log("Child " .. self._childName .. " leaving " .. self._locationName)

    local location = commandManager.locationsManager:findLocation(self._locationName)
    local child = commandManager.familyManager:findChild(self._childName)
    location:leaveChild(child)
end

---------------------------------------------------------------------------------
function DeselectChild.parseArgs(args)
    if #args < 1 then
        return nil, "Missing location name argument"
    end

    if #args < 2 then
        return nil, "Missing child name argument"
    end

    return args
end

return DeselectChild