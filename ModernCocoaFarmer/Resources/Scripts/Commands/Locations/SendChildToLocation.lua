local SendChildToLocation = {}

---------------------------------------------------------------------------------
function SendChildToLocation:new(locationName, childName)
    self._locationName = locationName
    self._childName = childName
end

---------------------------------------------------------------------------------
function SendChildToLocation:execute(commandManager)
    local location = commandManager.locationsManager:findLocation(self._locationName)
    if location == nil then
        log("Could not find location " .. self._locationName)
        return
    end

    local child = commandManager.familyManager:findChild(self._childName)
    if child == nil then
        log("Could not find child " .. self._childName)
        return
    end

    log(self._childName .. " is being sent to " .. self._locationName)
    commandManager.moneyManager:applyMoneyModifier(location:getMoneyModifier())
    location:sendChild(child)
end

---------------------------------------------------------------------------------
function SendChildToLocation.parseArgs(args)
    if #args < 1 then
        return nil, "Missing location name argument"
    end

    if #args < 2 then
        return nil, "Missing child name argument"
    end

    return args
end

return SendChildToLocation