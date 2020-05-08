local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local IncreaseSalaryLevelCommand = require 'Commands.Money.IncreaseSalaryLevel'
local SendNotification = require 'Commands.Notifications.SendNotification'

local SalaryIncreased = {}

---------------------------------------------------------------------------------
SalaryIncreased.NAME = "SalaryIncreased"
SalaryIncreased.PERIOD = GameEventPeriod.EVERY_MONTH
SalaryIncreased.MONTH_TO_TRIGGER = 5
SalaryIncreased.PROBABILITY_TO_TRIGGER = 0.33
SalaryIncreased.ICON_PATH = path.combine("Textures", "Icons", "Events", "SalaryIncreaseIcon.png")

---------------------------------------------------------------------------------
function SalaryIncreased.canTrigger(commandManager)
    return commandManager.timeManager:getCurrentMonth() == SalaryIncreased.MONTH_TO_TRIGGER and
           SalaryIncreased.PROBABILITY_TO_TRIGGER >= math.random()
end

---------------------------------------------------------------------------------
function SalaryIncreased.trigger(commandManager)
    commandManager:execute(IncreaseSalaryLevelCommand)
    commandManager:execute(
        SendNotification,
        "Salary Increased",
        "Your partner's pay has been increased!",
        SalaryIncreased.ICON_PATH)
end

return SalaryIncreased