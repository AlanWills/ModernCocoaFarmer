local Class = require 'OOP.Class'
local NotificationIcon = require 'UI.Notifications.NotificationIcon'

local NotificationsPanel = 
{
    NOTIFICATIONS_ANCHOR_NAME = "NotificationsAnchor",
    NOTIFICATION_ICON_PREFAB_PATH = path.combine("Prefabs", "UI", "Notifications", "NotificationIcon.prefab"),
    MAX_NUM_NOTIFICATIONS = 9,
}

---------------------------------------------------------------------------------
function NotificationsPanel.createNotificationIconCallback(notification, self)
    self:createNotificationIcon(notification) 
end

---------------------------------------------------------------------------------
function NotificationsPanel.removeNotificationCallback(caller, extraArgs)
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

    notificationManager:subscribeOnNotificationSentCallback(NotificationsPanel.createNotificationIconCallback, self)
end

---------------------------------------------------------------------------------
function NotificationsPanel:createNotificationIcon(notification)
    local notificationPrefab = Resources.loadPrefab(self.NOTIFICATION_ICON_PREFAB_PATH)
    local notificationGameObject = notificationPrefab:instantiate()
    local notificationIcon = Class.new(NotificationIcon, self._commandManager, notification, notificationGameObject)

    local notificationInteractionHandler = notificationGameObject:findComponent("MouseInteractionHandler")
    notificationInteractionHandler:subscribeOnLeftButtonUpCallback(NotificationsPanel.removeNotificationCallback, { self = self, notificationIcon = notificationIcon })
    notificationInteractionHandler:subscribeOnRightButtonUpCallback(NotificationsPanel.removeNotificationCallback, { self = self, notificationIcon = notificationIcon })

    self._notificationsAnchor:findComponent("StackPanel"):addChild(notificationGameObject)

    self:removeOldNotifications()
end

---------------------------------------------------------------------------------
function NotificationsPanel:removeNotification(notificationIcon)
    self._commandManager.notificationManager:removeNotification(notificationIcon._notification)
    self._notificationsAnchor:findComponent("StackPanel"):removeChild(notificationIcon._gameObject)
    notificationIcon._gameObject:destroy()
end

---------------------------------------------------------------------------------
function NotificationsPanel:removeOldNotifications()
    local numNotificationIcons = self._notificationsAnchor:getChildCount()
    
    for i = (numNotificationIcons - NotificationsPanel.MAX_NUM_NOTIFICATIONS - 1), 0, -1 do
        local notificationGameObject = self._notificationsAnchor:getChild(i)

        self._commandManager.notificationManager:removeNotification(i)
        self._notificationsAnchor:findComponent("StackPanel"):removeChild(notificationGameObject)
        notificationGameObject:destroy()
    end
end

return NotificationsPanel