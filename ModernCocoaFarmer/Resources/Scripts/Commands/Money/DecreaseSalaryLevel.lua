local DecreaseSalaryLevel = {}

---------------------------------------------------------------------------------
function DecreaseSalaryLevel:execute(commandManager)
    log("Decrementing salary level")
    commandManager.moneyManager:decrementSalaryLevel()
end

return DecreaseSalaryLevel