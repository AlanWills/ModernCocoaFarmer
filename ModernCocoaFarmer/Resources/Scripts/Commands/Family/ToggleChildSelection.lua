local ToggleChildSelection = {}

---------------------------------------------------------------------------------
function ToggleChildSelection:new(childName)
    self._childName = childName
end

---------------------------------------------------------------------------------
function ToggleChildSelection:execute(commandManager)
    log("Toggling child " .. self._childName .. " selection")
    commandManager.familyManager:toggleChildSelection(self._childName)
end

return ToggleChildSelection