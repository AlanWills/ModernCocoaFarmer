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

    commandManager.moneyManager:applyMoneyModifier(location:getMoneyModifier())
    location:sendChild(self._childName)
end

return SendChildToLocation