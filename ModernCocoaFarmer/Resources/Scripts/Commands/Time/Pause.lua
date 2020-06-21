local Pause = {}

---------------------------------------------------------------------------------
function Pause:execute(commandManager)
    log("Pausing game time")
    commandManager.timeManager:pause()
end

return Pause