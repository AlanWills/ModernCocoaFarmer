local GameEventPeriod = require 'GameEvents.GameEventPeriod'
local AddMoney = require 'Commands.Money.AddMoney'
local SendNotification = require 'Commands.Notifications.SendNotification'

local PayBills = {}

---------------------------------------------------------------------------------
PayBills.NAME = "PayBills"
PayBills.PERIOD = GameEventPeriod.EVERY_MONTH
PayBills.BASE_BILLS_MODIFIER_PATH = path.combine("Data", "Modifiers", "Events", "Money", "BaseBillsModifier.asset")
PayBills.CHILD_DEPENDENT_BILLS_MODIFIER_PATH = path.combine("Data", "Modifiers", "Events", "Money", "ChildDependentBillsModifier.asset")
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
function PayBills.trigger(commandManager)
    local amount = math.abs(PayBills.getTotalBillsAmount(commandManager.familyManager))

    commandManager:execute(AddMoney, amount)
    commandManager:execute(
        SendNotification,
        "Bills Are Due",
        string.format("You fork out %d for essentials", amount),
        PayBills.ICON_PATH)
end

return PayBills