local GetPaidSalary = {}

---------------------------------------------------------------------------------
GetPaidSalary.TIME_CONDITION_PATH = path.combine("Data", "Events", "Conditions", "Time", "Day25.asset")
GetPaidSalary.BASE_SALARY_MODIFIER = path.combine("Data", "Modifiers", "Events", "Money", "BaseSalaryLevel.asset")
GetPaidSalary.ICON_PATH = path.combine("Textures", "UI", "Utility", "Money.png")

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
function GetPaidSalary.paySalary(moneyManager, familyManager, locationManager, notificationManager)
    local salaryModifier = Modifier.create("Salary Modifier")
    salaryModifier:setAmount(GetPaidSalary.getSalaryAmount(moneyManager))
    salaryModifier:setChangeType("Delta")

    moneyManager:applyMoneyModifier(salaryModifier)
end

---------------------------------------------------------------------------------
function GetPaidSalary.showNotification(moneyManager, familyManager, locationManager, notificationManager)
    local notification = Notification.create("Pay Day!")

    notification:setDescription(string.format("Your partner's salary of %d has been paid", GetPaidSalary.getSalaryAmount(moneyManager)))
    notification:setIcon(GetPaidSalary.ICON_PATH)

    notificationManager:sendNotification(notification)
end

---------------------------------------------------------------------------------
function GetPaidSalary.register(gameEventManager)
    local gameEvent = GameEvent.create("Get Paid Salary")

    -- Conditions
    gameEvent:addCondition(GetPaidSalary.TIME_CONDITION_PATH)

    -- Effects
    local paySalaryEffect = LuaEffect.create("Pay Salary")
    paySalaryEffect:setTriggerFunc(GetPaidSalary.paySalary)

    local showNotificationEffect = LuaEffect.create("Show Notification")
    showNotificationEffect:setTriggerFunc(GetPaidSalary.showNotification)

    gameEvent:addEffect(paySalaryEffect)
    gameEvent:addEffect(showNotificationEffect)

    gameEventManager:registerGameEvent(gameEvent)
end

return GetPaidSalary