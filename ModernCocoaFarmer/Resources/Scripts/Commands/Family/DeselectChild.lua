local DeselectChild = {}

---------------------------------------------------------------------------------
function DeselectChild:new(childName)
    self._childName = childName
end

---------------------------------------------------------------------------------
function DeselectChild:execute(commandManager)
    log("Deselecting child " .. self._childName)
    commandManager.familyManager:deselectChild(self._childName)
end

return DeselectChild