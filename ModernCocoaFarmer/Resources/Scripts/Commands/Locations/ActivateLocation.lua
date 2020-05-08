local ActivateLocation = {}

---------------------------------------------------------------------------------
function ActivateLocation:new(locationName)
    self._locationName = locationName
end

---------------------------------------------------------------------------------
function ActivateLocation:execute(commandManager)
    log("Activating Location " .. self._locationName)
    commandManager.locationsManager:activateLocation(self._locationName)
end

return ActivateLocation