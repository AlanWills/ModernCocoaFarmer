local IncreaseSalaryLevel = {}

---------------------------------------------------------------------------------
function IncreaseSalaryLevel:execute(commandManager)
    log("Incrementing salary level")
    commandManager.moneyManager:incrementSalaryLevel()
end

return IncreaseSalaryLevel