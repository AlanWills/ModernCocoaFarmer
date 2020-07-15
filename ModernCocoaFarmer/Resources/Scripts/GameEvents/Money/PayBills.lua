local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local AddMoney = require 'Commands.Money.AddMoney'
local SendNotification = require 'Commands.Notifications.SendNotification'

local PayBills = {}

---------------------------------------------------------------------------------
PayBills.NAME = "PayBills"
PayBills.PERIOD = GameEventPeriod.EVERY_DAY
PayBills.DAY_TO_TRIGGER = 29
PayBills.BASE_BILLS_MODIFIER_PATH = path.combine("Data", "Modifiers", "Events", "Money", "BaseBillsModifier.asset")
PayBills.CHILD_DEPENDENT_BILLS_MODIFIER_PATH = path.combine("Data", "Modifiers", "Events", "Money", "ChildDependentBillsModifier.asset")
PayBills.DONT_PAY_BILLS_HEALTH_MODIFIER_PATH = path.combine("Data", "Modifiers", "Events", "Family", "DontPayBillsHealthModifier.asset")
PayBills.DONT_PAY_BILLS_SAFETY_MODIFIER_PATH = path.combine("Data", "Modifiers", "Events", "Family", "DontPayBillsSafetyModifier.asset")
PayBills.DONT_PAY_BILLS_EDUCATION_MODIFIER_PATH = path.combine("Data", "Modifiers", "Events", "Family", "DontPayBillsEducationModifier.asset")
PayBills.DONT_PAY_BILLS_HAPPINESS_MODIFIER_PATH = path.combine("Data", "Modifiers", "Events", "Family", "DontPayBillsHappinessModifier.asset")
PayBills.ICON_PATH = path.combine("Textures", "Icons", "Events", "PayBillsIcon.png")

---------------------------------------------------------------------------------
function PayBills.getBaseBillsAmount()
    local baseBillsModifier = Modifier.load(PayBills.BASE_BILLS_MODIFIER_PATH)
    return baseBillsModifier:getAmount()
end

---------------------------------------------------------------------------------
function PayBills.getChildDependentBillsAmount(familyManager)
    local childDependentModifier = Modifier.load(PayBills.CHILD_DEPENDENT_BILLS_MODIFIER_PATH)
    return childDependentModifier:getAmount() * familyManager:getChildCount()
end

---------------------------------------------------------------------------------
function PayBills.getTotalBillsAmount(familyManager)
    return PayBills.getBaseBillsAmount() + PayBills.getChildDependentBillsAmount(familyManager)
end

---------------------------------------------------------------------------------
function PayBills.canTrigger(commandManager)
    return commandManager.timeManager:getCurrentDay() == PayBills.DAY_TO_TRIGGER
end

---------------------------------------------------------------------------------
function PayBills.trigger(commandManager)
    local amount = PayBills.getTotalBillsAmount(commandManager.familyManager)
    local moneyManager = commandManager.moneyManager

    if moneyManager:getMoney() >= math.abs(amount) then
        commandManager:execute(AddMoney, amount)
        commandManager:execute(
            SendNotification,
            "Bills Are Due",
            string.format("You fork out %d for essentials", math.abs(amount)),
            PayBills.ICON_PATH)
    else
        local familyManager = commandManager.familyManager
        local dontPayBillsHealthModifier = Modifier.load(PayBills.DONT_PAY_BILLS_HEALTH_MODIFIER_PATH)
        local dontPayBillsSafetyModifier = Modifier.load(PayBills.DONT_PAY_BILLS_SAFETY_MODIFIER_PATH)
        local dontPayBillsEducationModifier = Modifier.load(PayBills.DONT_PAY_BILLS_EDUCATION_MODIFIER_PATH)
        local dontPayBillsHappinessModifier = Modifier.load(PayBills.DONT_PAY_BILLS_HAPPINESS_MODIFIER_PATH)

        familyManager:applyHealthModifier(dontPayBillsHealthModifier)
        familyManager:applySafetyModifier(dontPayBillsSafetyModifier)
        familyManager:applyEducationModifier(dontPayBillsEducationModifier)
        familyManager:applyHappinessModifier(dontPayBillsHappinessModifier)

        commandManager:execute(
            SendNotification,
            "Bills Are Due",
            string.format("You cannot afford the %d for essentials", math.abs(amount)),
            PayBills.ICON_PATH)
    end
end

return PayBills