local ElapseTime = {}

---------------------------------------------------------------------------------
function ElapseTime:new(elapsedTime)
    self.elapsedTime = elapsedTime
end

---------------------------------------------------------------------------------
function ElapseTime:execute(state)
    state.timeManager:update(self.elapsedTime)
end

return ElapseTime