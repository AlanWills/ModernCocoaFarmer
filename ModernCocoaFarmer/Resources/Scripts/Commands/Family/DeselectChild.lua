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

---------------------------------------------------------------------------------
function DeselectChild.parseArgs(args)
    if #args < 1 then
        return nil, "Missing child name argument"
    end

    return args
end

return DeselectChild