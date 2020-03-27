local ElapseTime = {}

---------------------------------------------------------------------------------
function ElapseTime:new(elapsedTime)
    self.elapsedTime = elapsedTime
end

---------------------------------------------------------------------------------
function ElapseTime:execute(commandManager)
    commandManager.timeManager:update(self.elapsedTime)
end

return ElapseTime