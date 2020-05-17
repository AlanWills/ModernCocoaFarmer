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

---------------------------------------------------------------------------------
function SelectChild.parseArgs(args)
    if #args < 1 then
        return nil, "Missing child name argument"
    end

    return args
end

return SelectChild