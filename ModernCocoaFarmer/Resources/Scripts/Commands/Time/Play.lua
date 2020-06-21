local Play = {}

---------------------------------------------------------------------------------
function Play:execute(commandManager)
    log("Resuming game time")
    commandManager.timeManager:play()
end

return Play