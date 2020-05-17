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

---------------------------------------------------------------------------------
function ActivateLocation.parseArgs(args)
    if #args < 1 then
        return nil, "Missing location name argument"
    end

    return args
end

return ActivateLocation