local SendChildToLocation = {}

---------------------------------------------------------------------------------
function SendChildToLocation:new(locationName, childName)
    self._locationName = locationName
    self._childName = childName
end

---------------------------------------------------------------------------------
function SendChildToLocation:execute(commandManager)
    local child = commandManager.familyManager:findChild(self._childName)
    if child == nil then
        log("Could not find child " .. self._childName)
        return
    end

    local location = commandManager.locationsManager:findLocation(self._locationName)
    if location == nil then
        log("Could not find location " .. self._locationName)
        return
    end

    location:sendChild(child)
end

return SendChildToLocation