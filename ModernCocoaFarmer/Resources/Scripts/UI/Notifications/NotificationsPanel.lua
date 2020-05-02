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
local function removeNotificationCallback(caller, extraArgs)
    extraArgs.self:removeNotification(extraArgs.notificationIcon)
end

---------------------------------------------------------------------------------
function NotificationsPanel:new(commandManager, notificationsPanelGameObject)
    self._commandManager = commandManager
    self._gameObject = notificationsPanelGameObject
    self._notificationsAnchor = notificationsPanelGameObject:findChild(self.NOTIFICATIONS_ANCHOR_NAME)

    local notificationManager = commandManager.notificationManager
    local notificationCount = 0

    while notificationCount < notificationManager:getNotificationCount() do
        self:createNotificationIcon(notificationManager:getNotification(notificationCount))
        notificationCount = notificationCount + 1
    end

    notificationManager:subscribeOnNotificationSentCallback(createNotificationIconCallback, self)
end

---------------------------------------------------------------------------------
function NotificationsPanel:createNotificationIcon(notification)
    local notificationPrefab = Resources.loadPrefab(self.NOTIFICATION_ICON_PREFAB_PATH)
    local notificationGameObject = notificationPrefab:instantiate()
    local notificationIcon = Class.new(NotificationIcon, self._commandManager, notification, notificationGameObject)

    local notificationInteractionHandler = notificationGameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(removeNotificationCallback, { self = self, notificationIcon = notificationIcon })
    notificationInteractionHandler:subscribeOnRightButtonUpCallback(removeNotificationCallback, { self = self, notificationIcon = notificationIcon })

    self._notificationsAnchor:findComponent("StackPanel"):addChild(notificationGameObject)
end

---------------------------------------------------------------------------------
function NotificationsPanel:removeNotification(notificationIcon)
    self._commandManager.notificationManager:removeNotification(notificationIcon._notification)
    self._notificationsAnchor:findComponent("StackPanel"):removeChild(notificationIcon._gameObject)
    notificationIcon._gameObject:destroy()
end

return NotificationsPanel