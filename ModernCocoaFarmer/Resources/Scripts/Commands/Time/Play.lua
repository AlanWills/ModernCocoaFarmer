local Play = {}

---------------------------------------------------------------------------------
function Play:execute(commandManager)
    commandManager.timeManager:play()
end

return Play