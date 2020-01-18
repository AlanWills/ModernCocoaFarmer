local Class = require 'OOP.Class'
local GameEventNotification = require 'UI.Events.GameEventNotification'

local GameEventsBar = {}

---------------------------------------------------------------------------------
local function createNotificationCallback(eventArgs, gameEvent, self)
    self:createNotification(gameEvent) 
end

---------------------------------------------------------------------------------
local function removeNotificationCallback(eventArgs, caller, extraArgs)
    extraArgs.self:removeNotification(extraArgs.notification)
end

---------------------------------------------------------------------------------
function GameEventsBar:new(gameEventBarGameObject, gameEventManager)
    self._gameObject = gameEventBarGameObject

    gameEventManager:subscribeOnGameEventTriggeredCallback(createNotificationCallback, self)
end

---------------------------------------------------------------------------------
function GameEventsBar:createNotification(gameEvent)
    if not gameEvent:getIcon():equals(nil) then
        local notification = Class.new(GameEventNotification, gameEvent, self._gameObject)
        local notificationInteractionHandler = notification.gameObject:findComponent("MouseInteractionHandler")
        notificationInteractionHandler:subscribeOnLeftButtonUpCallback(removeNotificationCallback, { self = self, notification = notification })
        notificationInteractionHandler:subscribeOnRightButtonUpCallback(removeNotificationCallback, { self = self, notification = notification })

        self._gameObject:findComponent("StackPanel"):addChild(notification.gameObject)
    end
end

---------------------------------------------------------------------------------
function GameEventsBar:removeNotification(notification)
    self._gameObject:findComponent("StackPanel"):removeChild(notification.gameObject)
    notification.gameObject:die()
end

return GameEventsBar