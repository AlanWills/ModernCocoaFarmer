local PayBills = {}

PayBills.TIME_CONDITION_PATH = path.combine("Data", "Events", "Conditions", "Time", "Day0.asset")
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
function PayBills.payBills(moneyManager, familyManager, locationManager, notificationManager)
    moneyManager:addMoney(PayBills.getTotalBillsAmount(familyManager))
end

---------------------------------------------------------------------------------
function PayBills.showNotification(moneyManager, familyManager, locationManager, notificationManager)
    local notification = Notification.create("Bills Are Due")

    notification:setDescription(string.format("You fork out %d for essentials", math.abs(PayBills.getTotalBillsAmount(familyManager))))
    notification:setIcon(PayBills.ICON_PATH)

    notificationManager:sendNotification(notification)
end

---------------------------------------------------------------------------------
function PayBills.register(gameEventManager)
    local gameEvent = GameEvent.create("Pay Bills")

    -- Conditions
    gameEvent:addCondition(PayBills.TIME_CONDITION_PATH)

    -- Effects
    local payBills = LuaEffect.create("Bills")
    payBills:setTriggerFunc(PayBills.payBills)
    
    local showNotificationEffect = LuaEffect.create("Show Notification")
    showNotificationEffect:setTriggerFunc(PayBills.showNotification)

    gameEvent:addEffect(payBills)
    gameEvent:addEffect(showNotificationEffect)

    gameEventManager:registerGameEvent(gameEvent)
end

return PayBills