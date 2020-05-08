local SelectChild = {}

---------------------------------------------------------------------------------
function SelectChild:new(childName)
    self._childName = childName
end

---------------------------------------------------------------------------------
function SelectChild:execute(commandManager)
    log("Selecting child " .. self._childName)
    commandManager.familyManager:selectChild(self._childName)
end

return SelectChild