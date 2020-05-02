local ActivateFirstChild = {}

---------------------------------------------------------------------------------
ActivateFirstChild.DAY_TO_TRIGGER = 20
ActivateFirstChild.MONTH_TO_TRIGGER = 0
ActivateFirstChild.YEAR_TO_TRIGGER = 0
ActivateFirstChild.ICON_PATH = path.combine("Textures", "Icons", "Events", "ChildBorn.png")

---------------------------------------------------------------------------------
function ActivateFirstChild.correctDaySinceStart(timeManager, moneyManager, familyManager)
    return timeManager:getCurrentDay() == ActivateFirstChild.DAY_TO_TRIGGER and
           timeManager:getCurrentMonth() == ActivateFirstChild.MONTH_TO_TRIGGER and
           timeManager:getCurrentYear() == ActivateFirstChild.YEAR_TO_TRIGGER
end

---------------------------------------------------------------------------------
function ActivateFirstChild.activateChild(moneyManager, familyManager, locationManager, notificationManager)
    familyManager:addChild()
end

---------------------------------------------------------------------------------
function ActivateFirstChild.showNotification(moneyManager, familyManager, locationManager, notificationManager)
    local notification = Notification.create("A Child!")
    local child = familyManager:getChild(familyManager:getChildCount() - 1)

    notification:setDescription("You welcome " .. child:getName() .. " as the newest member of the family")
    notification:setIcon(ActivateFirstChild.ICON_PATH)

    notificationManager:sendNotification(notification)
end

---------------------------------------------------------------------------------
function ActivateFirstChild.register(gameEventManager)
    local gameEvent = GameEvent.create("Child Born")

    -- Conditions
    local timeCondition = LuaCondition.create("Correct Time")
    timeCondition:setIsConditionMetFunc(ActivateFirstChild.correctDaySinceStart)

    gameEvent:addCondition(timeCondition)

    -- Effects
    local activateChildEffect = LuaEffect.create("Activate Child")
    activateChildEffect:setTriggerFunc(ActivateFirstChild.activateChild)

    local showNotificationEffect = LuaEffect.create("Show Notification")
    showNotificationEffect:setTriggerFunc(ActivateFirstChild.showNotification)

    gameEvent:addEffect(activateChildEffect)
    gameEvent:addEffect(showNotificationEffect)

    gameEventManager:registerGameEvent(gameEvent)
end

return ActivateFirstChild