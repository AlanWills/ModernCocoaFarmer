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

return DeselectChild