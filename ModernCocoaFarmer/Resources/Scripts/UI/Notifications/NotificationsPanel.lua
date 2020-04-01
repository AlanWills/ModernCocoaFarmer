local Class = require 'OOP.Class'
local NotificationIcon = require 'UI.Notifications.NotificationIcon'

local NotificationsPanel = 
{
    NOTIFICATIONS_ANCHOR_NAME = "NotificationsAnchor",
    NOTIFICATION_ICON_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationIcon.prefab"),
}

---------------------------------------------------------------------------------
local function createNotificationIconCallback(notification, self)
    self:createNotificationIcon(notification) 
end

---------------------------------------------------------------------------------
local function removeNotificationIconCallback(caller, extraArgs)
    extraArgs.self:removeNotificationIcon(extraArgs.notificationIcon._gameObject)
end

---------------------------------------------------------------------------------
function NotificationsPanel:new(commandManager, notificationsPanelGameObject)
    self._commandManager = commandManager
    self._gameObject = notificationsPanelGameObject
    self._notificationsAnchor = notificationsPanelGameObject:findChild(self.NOTIFICATIONS_ANCHOR_NAME)

    commandManager.notificationManager:subscribeOnNotificationSentCallback(createNotificationIconCallback, self)
end

---------------------------------------------------------------------------------
function NotificationsPanel:createNotificationIcon(notification)
    local notificationPrefab = Resources.loadPrefab(self.NOTIFICATION_ICON_PREFAB_PATH)
    local notificationGameObject = notificationPrefab:instantiate()
    local notificationIcon = Class.new(NotificationIcon, self._commandManager, notification, notificationGameObject)

    local notificationInteractionHandler = notificationGameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(removeNotificationIconCallback, { self = self, notificationIcon = notificationIcon })
    notificationInteractionHandler:subscribeOnRightButtonUpCallback(removeNotificationIconCallback, { self = self, notificationIcon = notificationIcon })

    self._notificationsAnchor:findComponent("StackPanel"):addChild(notificationGameObject)
end

---------------------------------------------------------------------------------
function NotificationsPanel:removeNotificationIcon(notificationGameObject)
    self._notificationsAnchor:findComponent("StackPanel"):removeChild(notificationGameObject)
    notificationGameObject:destroy()
end

return NotificationsPanel