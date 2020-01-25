local Class = require 'OOP.Class'
local NotificationIcon = require 'UI.Notifications.NotificationIcon'

local NotificationsBar = {}

---------------------------------------------------------------------------------
local function createNotificationIconCallback(eventArgs, gameEvent, self)
    self:createNotificationIcon(gameEvent) 
end

---------------------------------------------------------------------------------
local function removeNotificationIconCallback(eventArgs, caller, extraArgs)
    extraArgs.self:removeNotificationIcon(extraArgs.notificationIcon)
end

---------------------------------------------------------------------------------
function NotificationsBar:new(notificationsBarGameObject, notificationManager)
    self._gameObject = notificationsBarGameObject

    notificationManager:subscribeOnNotificationSentCallback(createNotificationIconCallback, self)
end

---------------------------------------------------------------------------------
function NotificationsBar:createNotificationIcon(notification)
    local notificationIcon = Class.new(NotificationIcon, notification, self._gameObject)
    local notificationInteractionHandler = notificationIcon.gameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(removeNotificationIconCallback, { self = self, notificationIcon = notificationIcon })
    notificationInteractionHandler:subscribeOnRightButtonUpCallback(removeNotificationIconCallback, { self = self, notificationIcon = notificationIcon })

    self._gameObject:findComponent("StackPanel"):addChild(notificationIcon.gameObject)
end

---------------------------------------------------------------------------------
function NotificationsBar:removeNotificationIcon(notificationIcon)
    self._gameObject:findComponent("StackPanel"):removeChild(notificationIcon.gameObject)
    notificationIcon.gameObject:die()
end

return NotificationsBar