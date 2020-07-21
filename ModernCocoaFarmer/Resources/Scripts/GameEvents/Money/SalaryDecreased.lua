local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local DecreaseSalaryLevelCommand = require 'Commands.Money.DecreaseSalaryLevel'
local SendNotification = require 'Commands.Notifications.SendNotification'

local SalaryDecreased = {}

---------------------------------------------------------------------------------
SalaryDecreased.NAME = "SalaryDecreased"
SalaryDecreased.PERIOD = GameEventPeriod.EVERY_MONTH
SalaryDecreased.MONTH_TO_TRIGGER = 11
SalaryDecreased.PROBABILITY_TO_TRIGGER = 0.4
SalaryDecreased.ICON_PATH = path.combine("Textures", "Icons", "Events", "SalaryDecreaseIcon.png")

---------------------------------------------------------------------------------
function SalaryDecreased.canTrigger(commandManager)
    return commandManager.timeManager:getCurrentMonth() == SalaryDecreased.MONTH_TO_TRIGGER and
           commandManager.moneyManager:getSalaryLevel() > 1 and 
           SalaryDecreased.PROBABILITY_TO_TRIGGER >= math.random()
end

---------------------------------------------------------------------------------
function SalaryDecreased.trigger(commandManager)
    commandManager:execute(DecreaseSalaryLevelCommand)
    commandManager:execute(
        SendNotification,
        "Salary Decreased",
        "Your partner's pay has been cut...",
        SalaryDecreased.ICON_PATH)
end

return SalaryDecreased