local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local AddMoney = require 'Commands.Money.AddMoney'
local SendNotification = require 'Commands.Notifications.SendNotification'

local GetPaidSalary = {}

---------------------------------------------------------------------------------
GetPaidSalary.NAME = "GetPaidSalary"
GetPaidSalary.PERIOD = GameEventPeriod.EVERY_DAY
GetPaidSalary.DAY_TO_TRIGGER = 28
GetPaidSalary.BASE_SALARY_MODIFIER = path.combine("Data", "Modifiers", "Events", "Money", "BaseSalaryLevel.asset")
GetPaidSalary.ICON_PATH = path.combine("Textures", "UI", "Utility", "Money.png")
GetPaidSalary.SFX_PATH = path.combine("Audio", "SFX", "Money.wav")

---------------------------------------------------------------------------------
function GetPaidSalary.getBaseSalaryAmount()
    local baseSalaryModifier = Modifier.load(GetPaidSalary.BASE_SALARY_MODIFIER)
    return baseSalaryModifier:getAmount()
end

---------------------------------------------------------------------------------
function GetPaidSalary.getSalaryAmount(moneyManager)
    return GetPaidSalary.getBaseSalaryAmount() * moneyManager:getSalaryLevel()
end

---------------------------------------------------------------------------------
function GetPaidSalary.canTrigger(commandManager)
    return commandManager.timeManager:getCurrentDay() == GetPaidSalary.DAY_TO_TRIGGER
end

---------------------------------------------------------------------------------
function GetPaidSalary.trigger(commandManager)
    local amount = GetPaidSalary.getSalaryAmount(commandManager.moneyManager)
    
    commandManager:execute(AddMoney, amount)
    commandManager:execute(
        SendNotification,
        "Pay Day!",
        string.format("Your partner's salary of %d has been paid", amount),
        GetPaidSalary.ICON_PATH,
        GetPaidSalary.SFX_PATH)
end

return GetPaidSalary