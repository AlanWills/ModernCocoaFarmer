local ElapseTime = {}

---------------------------------------------------------------------------------
function ElapseTime:new(elapsedTime)
    self.elapsedTime = elapsedTime
end

---------------------------------------------------------------------------------
function ElapseTime:execute(commandManager)
    commandManager.timeManager:update(self.elapsedTime)
end

---------------------------------------------------------------------------------
function ElapseTime.parseArgs(args)
    if #args < 1 then
        return nil, "Missing elapsed time argument"
    end

    args[1] = tonumber(args[1])
    return args
end

return ElapseTime