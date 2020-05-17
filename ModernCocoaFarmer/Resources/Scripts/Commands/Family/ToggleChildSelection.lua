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

---------------------------------------------------------------------------------
function ToggleChildSelection.parseArgs(args)
    if #args < 1 then
        return nil, "Missing child name argument"
    end

    return args
end

return ToggleChildSelection