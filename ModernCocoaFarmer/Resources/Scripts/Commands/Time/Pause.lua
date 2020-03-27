local Pause = {}

---------------------------------------------------------------------------------
function Pause:execute(commandManager)
    commandManager.timeManager:pause()
end

return Pause